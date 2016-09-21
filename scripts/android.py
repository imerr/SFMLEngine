import os
import sys
import subprocess
import shutil

config = {}
# commented out architectures don't have their dependencies included in sfml
# so for example libjpeg is missing for arm64-v8a and x86_64
architectures = [
	"armeabi",
	"armeabi-v7a",
#	"arm64-v8a",
	"x86",
#	"x86_64",
	"mips"
]
platformArch = {
	"armeabi" : "arch-arm",
	"armeabi-v7a" : "arch-arm",
	"arm64-v8a" : "arch-arm",
	"x86" : "arch-x86",
	"x86_64" : "arch-x86",
	"mips" : "arch-mips"
}


def main():
	if len(sys.argv) < 6:
		print "Usage: android.py <sourceDir> <buildDir> <NDK> <SDK> <buildTarget> [mode=Debug] [apiLevel=android-9]"
		sys.exit(1)
	global config, architectures
	config["source"] = os.path.abspath(sys.argv[1])
	config["build"] = os.path.abspath(sys.argv[2])
	config["ndk"] = sys.argv[3]
	config["sdk"] = sys.argv[4]
	config["target"] = sys.argv[5]
	config["mode"] = sys.argv[6] if len(sys.argv) >= 7 else "Debug"
	config["apiLevel"] = sys.argv[7] if len(sys.argv) >= 8 else "android-9"
	os.environ["ANDROID_NDK"] = config["ndk"]
	os.environ["ANDROID_SDK"] = config["sdk"]
	os.environ["PATH"] += "{2}{0}/tools{2}{0}/platform-tools{2}{1}".format(config["ndk"], config["sdk"], os.pathsep)
	try:
		os.mkdir(config["build"])
	except OSError: pass
	os.chdir(config["build"])
	for arch in architectures:
		if not cmake(arch): 
			print "CMake for", arch, "failed"
			sys.exit(1)
	for arch in architectures:
		if not ninja(arch): 
			print "Building (ninja) for", arch, "failed"
			sys.exit(1)
	# collect artifacts
	if os.path.exists("libs"):
		shutil.rmtree("libs")
	# copy openal.so..
	shutil.copytree(os.path.join(config["source"], "Engine/external/SFML/extlibs/libs-android"), "libs")
	for arch in architectures:
		collect(arch)
	# TODO: dont delete+copy, only sync
	print "Copying assets..."
	try:
		shutil.rmtree("assets")
	except OSError:
		pass
	os.mkdir("assets")
	shutil.copytree(os.path.join(config["source"], "assets"), "assets/assets")
	print "Copying res..."
	try:
		shutil.rmtree("res")
	except OSError:
		pass
	shutil.copytree(os.path.join(config["source"], "res"), "res")
	shutil.copy2(os.path.join(config["source"], "AndroidManifest.xml"), "AndroidManifest.xml")
	p = subprocess.Popen([
	os.path.join(config["sdk"], "tools/android.bat"),
		"update",
		"project",
		"--target",
		"1".format(config["apiLevel"]),
		"--path",
		"."
	])
	if p.wait() != 0:
		print "Updating project failed"
		sys.exit(1)
	p = subprocess.Popen([
		"ant.bat",
		"debug" if config["mode"] == "Debug" else "debug"
	])
	if p.wait() != 0:
		print "Building apk failed"
		sys.exit(1)
		
	
def archPath(arch):
	return "cmake_"+arch
	
def cmake(arch):
	global config
	print arch
	if os.path.exists(archPath(arch)):
		return True
	
	os.environ["SYSROOT"] = config["ndk"] + "/platforms/" + config["apiLevel"] + "/" + platformArch[arch]
	os.mkdir(archPath(arch))
	os.chdir(archPath(arch))
	p = subprocess.Popen([
		"cmake.exe",
		"-DANDROID_ABI=" + arch,
		"-DANDROID_NATIVE_API_LEVEL=" + config["apiLevel"],
		"-DCMAKE_TOOLCHAIN_FILE={0}/Engine/external/SFML/cmake/toolchains/android.toolchain.cmake".format(config["source"]),
		"-Wno-dev",
		"-GNinja",
		"-DCMAKE_BUILD_TYPE="+config["mode"],
		config["source"],
	])
	res = p.wait()
	os.chdir("..")
	return res == 0
	
def ninja(arch):
	global config
	print arch
	if not os.path.exists(archPath(arch)):
		print "Missing", archPath(arch)
		return False
	
	os.environ["SYSROOT"] = config["ndk"] + "/platforms/" + config["apiLevel"] + "/" + platformArch[arch]
	os.chdir(archPath(arch))
	p = subprocess.Popen([
		"ninja",
		config["target"],
		"sfml-activity"
	])
	#p.communicate()
	res = p.wait()
	os.chdir("..")
	return res == 0
	
def collect(arch):
	#os.mkdir("libs/"+arch)
	for subdir, dirs, files in os.walk(archPath(arch)):
		for file in files:
			if file.endswith(".so"):
				print "Collecting "+arch+ " " + file
				# sfml-activity check is a workaround for it always trying to load libsfml-activity.so
				shutil.copy2(os.path.join(subdir, file), "libs/" + arch + "/" + ("libsfml-activity.so" if file == "libsfml-activity-d.so" else file))
main()