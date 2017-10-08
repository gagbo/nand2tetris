all: Math Memory Screen Output Keyboard String Array Sys

%: %.jack
	@cp -lfv $< $@Test/$<
	../../tools/JackCompiler.sh $@Test
	@echo "Ready to run ../../tools/VMEmulator.sh\
	 on $@Test/$@Test.tst"
