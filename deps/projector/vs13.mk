#############################################################################################
#                                                                                           #   
#                  vcproj for Visual Studio 8 generator    (makefile project)               #
#                                                                                           #   
#                                    [EDITION 17]                                           #   
#############################################################################################

include $(MAK)

nmc-app:	
	$(info $(XML))

vc-app:		
	$(info $(VC_APP))
	
vc-lib:			
	$(info $(VC_LIB))	

#---------------------------------------------------------------------------------------------
# эта функция сворачивает пути обратно к виду $(VAR) если есть такая переменная с данным путем 
ifndef VarCollapse
define VarCollapse
$(subst $(NMPP),$$(NMPP),   $(subst $(NEURO),$$(NEURO),$(1))     )

endef
endif


#---------------------------------------------------------------------------------------------
#function of recurse search for *.h in argument directory
define recurse_scan_h
ALL_H+=$$(subst \,/,$$(shell find $(1) -name "*.h"   2>null))	
endef

#---------------------------------------------------------------------------------------------
# recurse scan *.h in $(HEADER_DIRS)
$(foreach d,$(HEADER_DIRS),$(eval $(call recurse_scan_h,$(d))))

#---------------------------------------------------------------------------------------------
empty:=
space:= $(empty) $(empty)
VAR_INC_PATH=$(call VarCollapse, $(INC_DIRS))
VAR_LIB_PATH=$(call VarCollapse, $(LIB_DIRS))
INC_PATH=$(subst ",,$(subst -I,;,$(subst $(space)-I,;,$(strip $(VAR_INC_PATH)))))
LIB_PATH=$(subst ",,$(subst -L,;,$(subst $(space)-L,;,$(strip $(VAR_LIB_PATH)))))
LIBS  := $(subst $(space),;,$(LIBS))
LIBSD := $(subst $(space),;,$(LIBSD))
#---------------------------------------------------------------------------------------------
define CR


endef
define TAB3
			
endef
define TAB2
		
endef
define TAB
	
endef

#---------------------------------------------------------------------------------------------
define VC_APP
<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" ToolsVersion="12.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|Win32">
      <Configuration>Debug</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|Win32">
      <Configuration>Release</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <ProjectGuid>{D9C40B01-91E0-4C5E-AEAE-0EC38ECB51B0}</ProjectGuid>
    <Keyword>Win32Proj</Keyword>
    <RootNamespace>$(PROJECT)</RootNamespace>
  </PropertyGroup>
  <Import Project="$$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$$(Configuration)|$$(Platform)'=='Debug|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v120</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$$(Configuration)|$$(Platform)'=='Release|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v120</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <Import Project="$$(VCTargetsPath)\Microsoft.Cpp.props" />
  <ImportGroup Label="ExtensionSettings">
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$$(Configuration)|$$(Platform)'=='Debug|Win32'">
    <Import Project="$$(UserRootDir)\Microsoft.Cpp.$$(Platform).user.props" Condition="exists('$$(UserRootDir)\Microsoft.Cpp.$$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$$(Configuration)|$$(Platform)'=='Release|Win32'">
    <Import Project="$$(UserRootDir)\Microsoft.Cpp.$$(Platform).user.props" Condition="exists('$$(UserRootDir)\Microsoft.Cpp.$$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <PropertyGroup Label="UserMacros" />
  <PropertyGroup Condition="'$$(Configuration)|$$(Platform)'=='Debug|Win32'">
    <LinkIncremental>true</LinkIncremental>
  </PropertyGroup>
  <PropertyGroup Condition="'$$(Configuration)|$$(Platform)'=='Release|Win32'">
    <LinkIncremental>false</LinkIncremental>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$$(Configuration)|$$(Platform)'=='Debug|Win32'">
    <ClCompile>
      <PrecompiledHeader>
      </PrecompiledHeader>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>Disabled</Optimization>
      <PreprocessorDefinitions>WIN32;_DEBUG;_CONSOLE;_LIB;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <AdditionalIncludeDirectories>$(INC_PATH)</AdditionalIncludeDirectories>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalDependencies>$(LIBSD)</AdditionalDependencies>
      <AdditionalLibraryDirectories>$(LIB_PATH)</AdditionalLibraryDirectories>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$$(Configuration)|$$(Platform)'=='Release|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <PrecompiledHeader>
      </PrecompiledHeader>
      <Optimization>MaxSpeed</Optimization>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <PreprocessorDefinitions>WIN32;NDEBUG;_CONSOLE;_LIB;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <AdditionalIncludeDirectories>$(INC_PATH)</AdditionalIncludeDirectories>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <AdditionalLibraryDirectories>$(LIB_PATH)</AdditionalLibraryDirectories>
      <AdditionalDependencies>$(LIBS)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemGroup>
  
endef


define ClCompile
VC_APP+=$$(TAB)<ClCompile Include="$(1)" /> $$(CR)
endef 
$(foreach cpp,$(ALL_CPP),$(eval $(call ClCompile,$(cpp)))	)
$(foreach c,  $(ALL_C),  $(eval $(call ClCompile,$(c)))	    )

define VC_APP1  
  </ItemGroup>
  <Import Project="$$(VCTargetsPath)\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets">
  </ImportGroup>
</Project>
endef

VC_APP+=$(VC_APP1)

#---------------------------------------------------------------------------------------------
define VC_LIB
<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" ToolsVersion="12.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|Win32">
      <Configuration>Debug</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|Win32">
      <Configuration>Release</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <ProjectGuid>{42D1F973-A2F8-4044-B1EC-0ECD841FA764}</ProjectGuid>
    <Keyword>Win32Proj</Keyword>
    <RootNamespace>nmpp_vs13</RootNamespace>
  </PropertyGroup>
  <Import Project="$$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$$(Configuration)|$$(Platform)'=='Debug|Win32'" Label="Configuration">
    <ConfigurationType>StaticLibrary</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v120</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$$(Configuration)|$$(Platform)'=='Release|Win32'" Label="Configuration">
    <ConfigurationType>StaticLibrary</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v120</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <Import Project="$$(VCTargetsPath)\Microsoft.Cpp.props" />
  <ImportGroup Label="ExtensionSettings">
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$$(Configuration)|$$(Platform)'=='Debug|Win32'">
    <Import Project="$$(UserRootDir)\Microsoft.Cpp.$$(Platform).user.props" Condition="exists('$$(UserRootDir)\Microsoft.Cpp.$$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$$(Configuration)|$$(Platform)'=='Release|Win32'">
    <Import Project="$$(UserRootDir)\Microsoft.Cpp.$$(Platform).user.props" Condition="exists('$$(UserRootDir)\Microsoft.Cpp.$$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <PropertyGroup Label="UserMacros" />
  <PropertyGroup />
  <ItemDefinitionGroup Condition="'$$(Configuration)|$$(Platform)'=='Debug|Win32'">
    <ClCompile>
      <PrecompiledHeader>
      </PrecompiledHeader>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>Disabled</Optimization>
      <PreprocessorDefinitions>WIN32;_DEBUG;_LIB;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <AdditionalIncludeDirectories>$(INC_PATH)</AdditionalIncludeDirectories>
    </ClCompile>
    <Link>
      <SubSystem>Windows</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
    </Link>
	 <Lib>
      <OutputFile>$(TARGETD)</OutputFile>
    </Lib>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$$(Configuration)|$$(Platform)'=='Release|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <PrecompiledHeader>
      </PrecompiledHeader>
      <Optimization>MaxSpeed</Optimization>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <PreprocessorDefinitions>WIN32;NDEBUG;_LIB;%(PreprocessorDefinitions)</PreprocessorDefinitions>
	  <AdditionalIncludeDirectories>$(INC_PATH)</AdditionalIncludeDirectories>
    </ClCompile>
    <Link>
      <SubSystem>Windows</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
    </Link>
	<Lib>
      <OutputFile>$(TARGET)</OutputFile>
    </Lib>
  </ItemDefinitionGroup>
  <ItemGroup>
    <Text Include="ReadMe.txt" />
  </ItemGroup>
  <ItemGroup>

endef 

define LIB_ClCompile
VC_LIB+=$$(TAB)<ClCompile Include="$(1)" /> $$(CR)
endef
$(foreach cpp,$(ALL_CPP),$(eval $(call LIB_ClCompile,$(cpp)))	)
$(foreach c,$(ALL_C),$(eval $(call LIB_ClCompile,$(c)))	)
  
define VC_LIB1  
  </ItemGroup>
  <Import Project="$$(VCTargetsPath)\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets">
  </ImportGroup>
</Project>

endef

VC_LIB+=$(VC_LIB1)
  
   