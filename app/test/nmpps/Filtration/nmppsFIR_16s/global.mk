
TOP_LEVEL:=d:/GIT/NMPP

#TOP_LEVEL:=$(realpath ../..)
TEMPLATES:=$(TOP_LEVEL)/nmpls/test/templates

PLATFORMS:=x86vs8 mc5103 mb7707 

export TOP_LEVEL	
export TEMPLATES
export PLATFORMS


test: test-x86vs8-mc5103
