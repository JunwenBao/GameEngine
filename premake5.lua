include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "GameEngine"
	architecture "x86_64"
	startproject "GameEngine-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "GameEngine/vendor/Box2D"
	include "GameEngine/vendor/GLFW"
	include "GameEngine/vendor/Glad"
	include "GameEngine/vendor/imgui"
	include "GameEngine/vendor/yaml-cpp"
group ""

include "GameEngine"
include "Sandbox"
include "GameEngine-Editor"