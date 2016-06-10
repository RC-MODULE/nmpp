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
$(subst $(NEURO),$$(NEURO),$(1))
endef
endif
#$(subst $(NMPP),$$(NMPP),   $(subst $(NEURO),$$(NEURO),$(1))     )

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
define XML
<?xml version="1.0" encoding="windows-1251"?>
<VisualStudioProject
	ProjectType="Visual C++"
	Version="8,00"
	Name="$(PROJECT)"
	ProjectGUID="{502FEC7E-393D-4397-8F70-5014080F458C}"
	RootNamespace="$(PROJECT)"
	Keyword="MakeFileProj"
	>
	<Platforms>
		<Platform
			Name="Win32"
		/>
	</Platforms>
	<ToolFiles>
	</ToolFiles>
	<Configurations>
		<Configuration
			Name="Debug|Win32"
			OutputDirectory="$$(ConfigurationName)"
			IntermediateDirectory="$$(ConfigurationName)"
			ConfigurationType="0"
			>
			<Tool
				Name="VCNMakeTool"
				BuildCommandLine="make DEBUG=y -j4"
				ReBuildCommandLine="make DEBUG=y -B -j4"
				CleanCommandLine="make DEBUG=y clean"
				Output="see makefile"
				PreprocessorDefinitions="NEURO;_DEBUG"
				IncludeSearchPath="$(INC_PATH)"
				ForcedIncludes=""
				AssemblySearchPath=""
				ForcedUsingAssemblies=""
				CompileAsManaged=""
			/>
		</Configuration>
		<Configuration
			Name="Release|Win32"
			OutputDirectory="$$(ConfigurationName)"
			IntermediateDirectory="$$(ConfigurationName)"
			ConfigurationType="0"
			>
			<Tool
				Name="VCNMakeTool"
				BuildCommandLine="make -j4"
				ReBuildCommandLine="make -B -j4"
				CleanCommandLine="make clean"
				Output="see makefile"
				PreprocessorDefinitions="WIN32;NDEBUG"
				IncludeSearchPath="$(INC_PATH)"
				ForcedIncludes=""			
				AssemblySearchPath=""
				ForcedUsingAssemblies=""
				CompileAsManaged=""
			/>
		</Configuration>
	</Configurations>
	<References>
	</References>
	<Files>
		<Filter
			Name="Source Files"
			Filter="cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx"
			UniqueIdentifier="{4FC737F1-C7A5-4376-A066-2A32D752A2FF}"
			>
			
endef
XML+=$(XML02)

define FileRelativePath
XML+=		<File RelativePath="$(1)" > </File> 
endef 
$(foreach cpp,$(ALL_CPP),$(eval $(call FileRelativePath,$(cpp)))	)

$(foreach asm,$(ALL_ASM),$(eval $(call FileRelativePath,$(asm)))	)

$(foreach c,$(ALL_C),$(eval $(call FileRelativePath,$(c)))	)
XML+=</Filter>



define XML03 
	
		<Filter
			Name="Header Files"
			Filter="h;hpp;hxx;hm;inl;inc;xsd"
			UniqueIdentifier="{93995380-89BD-4b04-88EB-625FBE52EBFB}"
		>
		
endef		

XML+=$(XML03)

define FileRelativePathH
XML+=		<File RelativePath="$(1)" > </File> 
endef 
$(foreach h,$(ALL_H),$(eval $(call FileRelativePathH,$(h)))	)

XML+=</Filter>



$(foreach res,$(RESOURCES),$(eval $(call FileRelativePathH,$(res)))	)
			
define XML05
		</Files>
	<Globals>
	</Globals>
</VisualStudioProject>
endef 
XML+=$(XML05)

##################################################################################################
############################ Generation vcproj(VS8) for x86 Visual studio application ############
##################################################################################################
define VC_APP
<?xml version="1.0" encoding="windows-1251"?>
<VisualStudioProject
	ProjectType="Visual C++"
	Version="8,00"
	Name="$(PROJECT)"
	ProjectGUID="{502FEC7E-393D-4397-8F70-5014080F458C}"
	RootNamespace="$(PROJECT)"
	>
	<Platforms>
		<Platform
			Name="Win32"
		/>
	</Platforms>
	<ToolFiles>
	</ToolFiles>
	<Configurations>
		<Configuration
			Name="Release|Win32"
			OutputDirectory=".\Release"
			IntermediateDirectory=".\Release"
			ConfigurationType="1"
			InheritedPropertySheets="$$(VCInstallDir)VCProjectDefaults\UpgradeFromVC60.vsprops"
			UseOfMFC="0"
			ATLMinimizesCRunTimeLibraryUsage="false"
			CharacterSet="2"
			>
		
			<Tool
				Name="VCCLCompilerTool"
				Optimization="2"
				InlineFunctionExpansion="1"
				AdditionalIncludeDirectories="$(INC_PATH)" 
				PreprocessorDefinitions="NDEBUG;WIN32;_CONSOLE;"
				StringPooling="true"
				RuntimeLibrary="2"
				EnableFunctionLevelLinking="true"
				PrecompiledHeaderFile=".\Release/tmp.pch"
				AssemblerListingLocation=".\Release/"
				ObjectFile=".\Release/"
				ProgramDataBaseFileName=".\Release/"
				WarningLevel="3"
				SuppressStartupBanner="true"
			/>
		
			<Tool
				Name="VCLinkerTool"
				AdditionalDependencies="$(LIBS) "
				OutputFile="$(TARGET)"
				LinkIncremental="1"
				SuppressStartupBanner="true"
				AdditionalLibraryDirectories="$(LIB_PATH)"
				ProgramDatabaseFile=".\Release/tmp.pdb"
				SubSystem="1"
				TargetMachine="1"
			/>
		
		</Configuration>
		<Configuration
			Name="Debug|Win32"
			OutputDirectory=".\Debug"
			IntermediateDirectory=".\Debug"
			ConfigurationType="1"
			InheritedPropertySheets="$$(VCInstallDir)VCProjectDefaults\UpgradeFromVC60.vsprops"
			UseOfMFC="0"
			ATLMinimizesCRunTimeLibraryUsage="false"
			CharacterSet="2"
			ManagedExtensions="0"
			>
			<Tool
				Name="VCCLCompilerTool"
				Optimization="0"
				AdditionalIncludeDirectories="$(INC_PATH)" 	
				PreprocessorDefinitions="_DEBUG;WIN32;_CONSOLE;"
				MinimalRebuild="false"
				BasicRuntimeChecks="0"
				RuntimeLibrary="3"
				PrecompiledHeaderFile=".\Debug/tmp.pch"
				AssemblerListingLocation=".\Debug/"
				ObjectFile=".\Debug/"
				ProgramDataBaseFileName=".\Debug/"
				WarningLevel="3"
				SuppressStartupBanner="true"
				DebugInformationFormat="3"
			/>
			<Tool
				Name="VCManagedResourceCompilerTool"
			/>
			<Tool
				Name="VCResourceCompilerTool"
				PreprocessorDefinitions="_DEBUG"
				Culture="1033"
			/>
			<Tool
				Name="VCLinkerTool"
				AdditionalDependencies="$(LIBSD)"
				OutputFile="$(TARGETD)"
				LinkIncremental="2"
				SuppressStartupBanner="true"
				AdditionalLibraryDirectories="$(LIB_PATH)"
				GenerateDebugInformation="true"
				AssemblyDebug="1"
				ProgramDatabaseFile=".\Debug/tmp.pdb"
				SubSystem="1"
				TargetMachine="1"
			/>
		</Configuration>
	</Configurations>
	<Files>
		<Filter
			Name="Source Files"
			Filter="cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx"
			UniqueIdentifier="{4FC737F1-C7A5-4376-A066-2A32D752A2FF}"
			>
endef

define FileRelativePath2
VC_APP+=$$(TAB3)<File RelativePath="$(subst /,\,$(1))" > </File>$$(CR)
endef 

$(foreach cpp,$(ALL_CPP),$(eval $(call FileRelativePath2,$(cpp)))	)

$(foreach asm,$(ALL_ASM),$(eval $(call FileRelativePath2,$(asm)))	)

$(foreach c,  $(ALL_C),  $(eval $(call FileRelativePath2,$(c)))	    )  

VC_APP+=</Filter> $(CR)

define VC_APP5 
		<Filter
			Name="Header Files"
			Filter="h;hpp;hxx;hm;inl;inc;xsd"
			UniqueIdentifier="{93995380-89BD-4b04-88EB-625FBE52EBFB}"
		>
endef		

VC_APP+=$(VC_APP5) $(CR)

define FileRelativePathH2
VC_APP+=$$(TAB3)<File RelativePath="$(1)" > </File> $$(CR)
endef 
$(foreach cpp,$(ALL_H),$(eval $(call FileRelativePathH2,$(cpp)))	)
VC_APP+=$(TAB2)</Filter> $(CR)


$(foreach cpp,$(RESOURCES),$(eval $(call FileRelativePathH2,$(cpp)))	)


			
define VC_APP6
		</Files>
	<Globals>
	</Globals>
</VisualStudioProject>
endef 
VC_APP+=$(VC_APP6)

##################################################################################################
############################ Generation vcproj(VS8) for x86 Visual studio library     ############
##################################################################################################
define VC_LIB
<?xml version="1.0" encoding="windows-1251"?>
<VisualStudioProject
	ProjectType="Visual C++"
	Version="8,00"
	Name="$(PROJECT)"
	ProjectGUID="{502FEC7E-393D-4397-8F70-5014080F458C}"
	RootNamespace="$(PROJECT)"
	>
	<Platforms>
		<Platform
			Name="Win32"
		/>
	</Platforms>
	<ToolFiles>
	</ToolFiles>
	<Configurations>
		<Configuration
			Name="Release|Win32"
			OutputDirectory="$$(SolutionDir)$$(ConfigurationName)"
			IntermediateDirectory="$$(ConfigurationName)"
			ConfigurationType="4"
			CharacterSet="1"
			WholeProgramOptimization="1"
			>
		
			<Tool
				Name="VCCLCompilerTool"
				AdditionalIncludeDirectories="$(INC_PATH)"
				PreprocessorDefinitions="WIN32;NDEBUG;_LIB"
				RuntimeLibrary="2"
				UsePrecompiledHeader="0"
				WarningLevel="3"
				Detect64BitPortabilityProblems="true"
				DebugInformationFormat="3"
				
			/>
		
			<Tool
				Name="VCLibrarianTool"
				OutputFile="$(TARGET)"
			/>
		
		</Configuration>
		<Configuration
			Name="Debug|Win32"
			OutputDirectory="$$(SolutionDir)$$(ConfigurationName)"
			IntermediateDirectory="$$(ConfigurationName)"
			ConfigurationType="4"
			CharacterSet="1"
			>
			<Tool
				Name="VCCLCompilerTool"
				Optimization="0"
				AdditionalIncludeDirectories="$(INC_PATH)"
				PreprocessorDefinitions="WIN32;_DEBUG;_LIB"
				MinimalRebuild="true"
				BasicRuntimeChecks="3"
				RuntimeLibrary="3"
				UsePrecompiledHeader="0"
				WarningLevel="3"
				Detect64BitPortabilityProblems="true"
				DebugInformationFormat="4"
			/>
			<Tool
				Name="VCLibrarianTool"
				OutputFile="$(TARGETD)"
			/>
		</Configuration>
	</Configurations>
	<Files>
		<Filter
			Name="Source Files"
			Filter="cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx"
			UniqueIdentifier="{4FC737F1-C7A5-4376-A066-2A32D752A2FF}"
			>

endef

define FileRelativePath2
VC_LIB+=$$(TAB3)<File RelativePath="$(subst /,\,$(1))" > </File> $$(CR)
endef 

$(foreach cpp,$(ALL_CPP),$(eval $(call FileRelativePath2,$(cpp)))	)

$(foreach asm,$(ALL_ASM),$(eval $(call FileRelativePath2,$(asm)))	)

$(foreach c,  $(ALL_C),  $(eval $(call FileRelativePath2,$(c)))	    )


VC_LIB+=$(TAB2)</Filter> $(CR)

define VC_LIB5 
		<Filter
			Name="Header Files"
			Filter="h;hpp;hxx;hm;inl;inc;xsd"
			UniqueIdentifier="{93995380-89BD-4b04-88EB-625FBE52EBFB}"
		>
endef		

VC_LIB+=$(VC_LIB5) $(CR)

define FileRelativePathH2
VC_LIB+=$$(TAB3)<File RelativePath="$(1)" > </File> $$(CR)
endef 
$(foreach cpp,$(ALL_H),$(eval $(call FileRelativePathH2,$(cpp)))	)

VC_LIB+=$(TAB2)</Filter> $(CR)


$(foreach cpp,$(RESOURCES),$(eval $(call FileRelativePathH2,$(cpp)))	)
			
define VC_LIB6
	</Files>
	<Globals>
	</Globals>
</VisualStudioProject>
endef 
VC_LIB+=$(VC_LIB6)


