/* 
 * File:   Node.cpp
 * Author: iMer
 * 
 * Created on 3. Juli 2014, 01:00
 */

#include "Node.hpp"
#include "util/math.hpp"
#include "Scene.hpp"
#include <iostream>
namespace engine {

    Node::Node(Scene* scene) : m_scene(scene), m_parent(nullptr), m_body(nullptr), m_parentJoint(nullptr), m_size(0, 0), m_opaque(true) {
    }

    Node::~Node() {
        if (m_body) {
            m_scene->GetWorld()->DestroyBody(m_body);
            m_body = nullptr;
        }
    }

    void Node::draw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
        // apply the transform
        if (m_body) {
            UpdateTransform(delta);
            states = sf::RenderStates::Default;
        }
        states.transform *= getTransform();
        OnDraw(target, states);
        for (auto it = m_children.begin(); it != m_children.end(); it++) {
            (*it)->draw(target, states, delta);
        }
        PostDraw(target, states);
    }

    void Node::AddNode(Node* node) {
        m_children.push_back(node);
        node->SetParent(this);
        node->SetScene(m_scene);
    }

    void Node::RemoveNode(Node* node) {
        m_children.remove(node);
    }

    void Node::SetScene(Scene* scene) {
        m_scene = scene;
        for (auto it = m_children.begin(); it != m_children.end(); it++) {
            (*it)->SetScene(scene);
        }
    }

    Scene* Node::GetScene() const {
        return m_scene;
    }

    void Node::SetParent(Node* parent) {
        m_parent = parent;
    }

    Node* Node::GetParent() const {
        return m_parent;
    }

    sf::Transform Node::GetGlobalTransform() {
        if (m_parent) {
            return m_parent->GetGlobalTransform() * getTransform();
        }
        return getTransform();
    }

    sf::Vector2f Node::GetGlobalPosition() {
        return GetGlobalTransform().transformPoint(0, 0);
    }

    void Node::update(sf::Time interval) {
        if (m_body) {
            UpdatePhysicsTransform();
        }
        OnUpdate(interval);
        for (auto it = m_children.begin(); it != m_children.end(); it++) {
            (*it)->update(interval);
        }
    }

    void Node::UpdatePhysicsTransform() {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_physicsTransform.rot = m_body->GetAngle()*180 / util::fPI;
        m_physicsTransform.rotVel = m_body->GetAngularVelocity()*180 / util::fPI;
        m_physicsTransform.pos = m_body->GetPosition();
        m_physicsTransform.pos *= m_scene->GetPixelMeterRatio();
        m_physicsTransform.vel = m_body->GetLinearVelocity();
        m_physicsTransform.vel *= m_scene->GetPixelMeterRatio();
    }

    void Node::UpdateTransform(float delta) {
        std::lock_guard<std::mutex> lg(m_mutex);
        setRotation(m_physicsTransform.rot);
        setPosition(m_physicsTransform.pos.x, m_physicsTransform.pos.y);
    }

    bool Node::initialize(Json::Value& root) {
        m_opaque = root.get("opaque", true).asBool();
        if (root.isMember("size")) {
            auto size = root["size"];
            if (size.isArray()) {
                m_size.x = size.get(0u, 0).asFloat();
                m_size.y = size.get(1u, 0).asFloat();
            } else {
                m_size.x = size.get("x", 0).asFloat();
                m_size.y = size.get("y", 0).asFloat();
            }
        }

        if (root.isMember("origin")) {
            auto origin = root["origin"];
            if (origin.isArray()) {
                setOrigin(origin.get(0u, m_size.x / 2).asInt(), origin.get(1u, m_size.y / 2).asInt());
            } else if (origin.isObject()) {
                setOrigin(origin.get("x", m_size.x / 2).asInt(), origin.get("y", m_size.y / 2).asInt());
            } else {
                std::string sorigin = origin.asString();
                if (sorigin == "top-left") {
                    setOrigin(0, 0);
                } else if (sorigin == "top-right") {
                    setOrigin(m_size.x, 0);
                } else if (sorigin == "bottom-left") {
                    setOrigin(0, m_size.y);
                } else if (sorigin == "bottom-right") {
                    setOrigin(m_size.x, m_size.y);
                } else if (sorigin == "center-right") {
                    setOrigin(m_size.x, m_size.y / 2);
                } else if (sorigin == "center-left") {
                    setOrigin(m_size.x, m_size.y / 2);
                } else { // Center
                    setOrigin(m_size.x / 2, m_size.y / 2);
                }
            }
        }
        if (root.isMember("position") && root.isMember("body")) {
            root["body"]["position"] = root["position"];
        } else if (root["position"].isArray()) {
            setPosition(root["position"].get(0u, 0).asFloat(), root["position"].get(1u, 0).asFloat());
        } else if (root["position"].isObject()) {
            setPosition(root["position"].get("x", 0).asFloat(), root["position"].get("y", 0).asFloat());
        }
        if (root.isMember("body")) {
            auto jbody = root["body"];
            b2BodyDef body;
            body.active = jbody.get("active", true).asBool();
            body.allowSleep = jbody.get("allowSleep", true).asBool();
            body.angle = jbody.get("angle", 0.0f).asFloat() * util::fPI / 180;
            body.angularDamping = jbody.get("angularDamping", 0.0f).asFloat();
            body.angularVelocity = jbody.get("angularVelocity", 0.0f).asFloat() * util::fPI / 180;
            body.awake = jbody.get("awake", true).asBool();
            body.bullet = jbody.get("bullet", false).asBool();
            body.fixedRotation = jbody.get("fixedRotation", false).asBool();
            body.gravityScale = jbody.get("gravityScale", 1.0f).asFloat();
            body.linearDamping = jbody.get("linearDamping", 0.0f).asFloat();
            if (jbody.isMember("linearVelocity")) {
                auto velocity = jbody["linearVelocity"];
                body.linearVelocity.x = velocity.get("x", 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                body.linearVelocity.y = velocity.get("y", 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
            }
            if (jbody.isMember("position")) {
                auto pos = jbody["position"];
                if ((pos.isArray() || pos.isObject()) && m_parent && m_parent->GetBody()) {
                    body.position = m_parent->GetBody()->GetPosition();
                }
                if (pos.isArray()) {
                    body.position.x += pos.get(0u, 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                    body.position.y += pos.get(1u, 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                } else {
                    body.position.x += pos.get("x", 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                    body.position.y += pos.get("y", 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                }
            }
            body.userData = this;
            std::string type = jbody.get("type", "dynamic").asString();
            if (type == "static") {
                body.type = b2_staticBody;
            } else if (type == "dynamic") {
                body.type = b2_dynamicBody;
            } else if (type == "kinematic") {
                body.type = b2_kinematicBody;
            }
            m_body = GetScene()->GetWorld()->CreateBody(&body);
            if (jbody.isMember("shapes")) {
                auto shapes = jbody["shapes"];
                if (!shapes.empty() && shapes.isArray()) {
                    for (unsigned int i = 0; i < shapes.size(); i++) {
                        std::string shapeType = shapes[i].get("type", "box").asString();
                        b2PolygonShape poly;
                        b2FixtureDef def;
                        b2ChainShape chain;
                        b2CircleShape circle;
                        b2EdgeShape edge;
                        def.density = shapes[i].get("density", 0.0f).asFloat();
                        def.friction = shapes[i].get("friction", 0.2f).asFloat();
                        def.restitution = shapes[i].get("restitution", 0.0f).asFloat();
                        def.isSensor = shapes[i].get("isSensor", false).asFloat();
                        if (shapeType == "box") {
                            float width = shapes[i].get("width", 1.0f).asFloat() / 2 / m_scene->GetPixelMeterRatio();
                            float height = shapes[i].get("height", 1.0f).asFloat() / 2 / m_scene->GetPixelMeterRatio();
                            poly.SetAsBox(width, height, b2Vec2(0, 0), shapes[i].get("angle", 0.0f).asFloat() * util::fPI / 180);
                            def.shape = &poly;
                        } else if (shapeType == "polygon") {
                            auto points = shapes[i]["points"];
                            if (points.isArray()) {
                                if (points.size() > b2_maxPolygonVertices) {
                                    std::cerr << "Too many vertices!" << std::endl;
                                    continue;
                                }
                                b2Vec2 b2points[b2_maxPolygonVertices];
                                for (size_t o = 0; o < points.size(); o++) {
                                    b2points[o].x = points[o].get(0u, 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                                    b2points[o].y = points[o].get(1u, 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                                }
                                poly.Set(b2points, points.size());
                                def.shape = &poly;

                            } else {
                                std::cerr << "Couldn't create fixture, points is no array" << std::endl;
                                continue;
                            }

                        } else if (shapeType == "circle") {
                            circle.m_p.x = shapes[i].get("x", 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                            circle.m_p.y = shapes[i].get("y", 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                            circle.m_radius = shapes[i].get("radius", .5f).asFloat();
                            def.shape = &circle;
                        } else if (shapeType == "edge") {

                            auto points = shapes[i]["points"];
                            if (points.isArray() && points.size() == 2) {
                                edge.Set(b2Vec2(points[0u].get("x", 0.0f).asFloat() / m_scene->GetPixelMeterRatio(), points[0u].get("y", 0.0f).asFloat() / m_scene->GetPixelMeterRatio()), b2Vec2(points[1u].get("x", 0.0f).asFloat() / m_scene->GetPixelMeterRatio(), points[1u].get("y", 0.0f).asFloat() / m_scene->GetPixelMeterRatio()));
                            } else {
                                std::cerr << "Did not provide 2 points for edge shape" << std::endl;
                                continue;
                            }
                            // ghost vert
                            if (!shapes[i]["prev"].empty()) {
                                edge.m_hasVertex0 = true;
                                edge.m_vertex0.x = shapes[i]["prev"].get("x", 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                                edge.m_vertex0.y = shapes[i]["prev"].get("y", 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                            }
                            if (!shapes[i]["next"].empty()) {
                                edge.m_hasVertex3 = true;
                                edge.m_vertex3.x = shapes[i]["next"].get("x", 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                                edge.m_vertex3.y = shapes[i]["next"].get("y", 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                            }
                            def.shape = &edge;
                        } else if (shapeType == "chain") {
                            if (shapes[i]["points"].isArray() && shapes[i]["points"].size()) {
                                auto p = shapes[i]["points"];
                                b2Vec2* points = new b2Vec2[p.size()];
                                for (unsigned int o = 0; o < p.size(); o++) {
                                    points[o].x = p[o].get("x", 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                                    points[o].y = p[o].get("y", 0.0f).asFloat() / m_scene->GetPixelMeterRatio();
                                }

                                chain.CreateChain(points, p.size());
                                // ghost vert
                                if (!shapes[i]["prev"].empty()) {
                                    chain.SetPrevVertex(b2Vec2(shapes[i]["prev"].get("x", 0.0f).asFloat() / m_scene->GetPixelMeterRatio(), shapes[i]["prev"].get("y", 0.0f).asFloat() / m_scene->GetPixelMeterRatio()));
                                }
                                if (!shapes[i]["next"].empty()) {
                                    chain.SetPrevVertex(b2Vec2(shapes[i]["next"].get("x", 0.0f).asFloat() / m_scene->GetPixelMeterRatio(), shapes[i]["next"].get("y", 0.0f).asFloat() / m_scene->GetPixelMeterRatio()));
                                }
                                delete points;
                            } else {
                                std::cerr << "No points for chain shape provided" << std::endl;
                                continue;
                            }
                        } else {
                            std::cerr << "Unknown shape type" << std::endl;
                        }
                        m_body->CreateFixture(&def);
                        if (m_parent && m_parent->GetBody()) { // Create joint
                            std::cout << "Creating parented joint" << std::endl;
                            auto joint = jbody["joint"];
                            std::string jtype = joint.get("type", "revolute").asString();
                            b2Vec2 anchorA = m_parent->GetBody()->GetPosition();
                            b2Vec2 anchorB = m_body->GetPosition();
                            if (joint["anchor"].isArray() && joint["anchor"].size() == 2 && (joint["anchor"][0u].isArray() || joint["anchor"][0u].isObject())) {
                                anchorA.x = m_parent->GetBody()->GetPosition().x + joint["anchor"][0u].get(0u, 0).asFloat() / m_scene->GetPixelMeterRatio();
                                anchorA.y = m_parent->GetBody()->GetPosition().y + joint["anchor"][0u].get(1u, 0).asFloat() / m_scene->GetPixelMeterRatio();
                                anchorB.x = m_body->GetPosition().x + joint["anchor"][1u].get(0u, 0).asFloat() / m_scene->GetPixelMeterRatio();
                                anchorB.y = m_body->GetPosition().y + joint["anchor"][1u].get(1u, 0).asFloat() / m_scene->GetPixelMeterRatio();
                            } else {
                                anchorA.x = m_parent->GetBody()->GetPosition().x + joint["anchor"].get(0u, 0).asFloat() / m_scene->GetPixelMeterRatio();
                                anchorA.y = m_parent->GetBody()->GetPosition().y + joint["anchor"].get(1u, 0).asFloat() / m_scene->GetPixelMeterRatio();
                            }
                            // TODO: Expand on this as needed
                            if (jtype == "revolute") {
                                b2RevoluteJointDef rev;
                                rev.Initialize(m_parent->GetBody(), m_body, anchorA);
                                m_parentJoint = m_scene->GetWorld()->CreateJoint(&rev);
                            } else if (jtype == "distance") {
                                b2DistanceJointDef dist;
                                dist.Initialize(m_parent->GetBody(), m_body, anchorA, anchorB);
                                m_parentJoint = m_scene->GetWorld()->CreateJoint(&dist);
                            } else if (jtype == "weld") {
                                b2WeldJointDef weld;
                                weld.Initialize(m_parent->GetBody(), m_body, anchorA);
                                m_parentJoint = m_scene->GetWorld()->CreateJoint(&weld);
                                
                            }
                        }
                    }
                }
            }
        }

        return true;
    }

    uint8_t Node::GetType() const {
        return NT_NONE;
    }

    void Node::SetOpaque(bool opaque) {
        m_opaque = opaque;
    }

    bool Node::IsOpaque() const {
        return m_opaque;
    }

    void Node::SetPosition(float x, float y) {
        std::lock_guard<std::mutex> lg(m_mutex);
        if (m_body) {
            m_body->SetTransform(b2Vec2(x, y), m_body->GetAngle());
        } else {
            setPosition(x, y);
        }
    }

    b2Body* Node::GetBody() const {
        return m_body;
    }

    b2Joint* Node::GetParentJoint() const {
        return m_parentJoint;
    }
}

