print (arg[1], arg[2], '\n')

local map_file = arg[1]

-------- список функций с нестандартным соглашанием о передаче параметров  (заключаются в PROFILE_NONSTD_FUNC )----------
nonstd_funcs  = { "list","FAdd","Mul32","FMul","IDiv32","UDiv32","FDiv","IMod32","UMod32","LShift32","RShift32","ARShift32","ConvI64toF","ConvU64toF" }
-------- функции из этих секций не будут профилироваться ------------------
exclude_sections = {".text_nmvcore", ".text_profiler"}
-------- функции, начинающиеся с этих слов не будут профилироваться ----------------
exclude_prefixes = {"_realloc", "_profiler","___","_ncl","_void._.0.8.8alloc_somewhere"}
-------- функции со следущими именами не будут профилироваться   ----------
exclude_funcs = {	"start",
					"_clock",
					"clock_initialize",
					"_exit",
					"__exit",
					"_abort",
					"_DestructFloat",
					"_ConstructFloat",
					"_DstrDouble",
					"_ConstructDouble",
					"_stderr",
					"_err_msg",
					"_mes",
					"loadStackAddr",
					"_longjmp",
					"_setjmp",
					"_int._.0.8.8beginMessage.1.2",
					"_boardOutServBuf",
					"_boardSend",
					"_sended",
					"_sendMostDistant",
					"_nm_io_debug",
					"_sendConfirmed",
					"stop",
					"_vsprintf",
					"_void._std.8.8terminate.1.2",
					"_printf",
					"_ncl_hostSync",
					"_void0._.0.8.8alloc_somewhere.1void._.0.9._unsigned._int.9._class.__heap_control_block._.0.2"
				}

--"_void._.8.8swapBuffers.1.2",
--"_int._.0.8.8currBuffer",
--"_int._.8.8inBuffer",
--"_void._.8.8dummy.1.2",
function has_element(element,array)			
	for key,val in pairs(array) do
		if val==element then
			return true
		end
	end
	return false
end 				

function has_prefix(element,array)			
	for key,val in pairs(array) do
		if string.match(element,val) then
			return true
		end
	end
	return false
end 				


--if have_element("list",nonstd_funcs) then
--	print ("*****nonst********")
--end
--
--if have_prefix("_profiler",exclude_prefixes) then
--	print ("*****profiler********")
--end

-- see if the file exists
function file_exists(file)
  local f = io.open(file, "rb")
  if f then f:close() end
  return f ~= nil
end

-- get all lines from a file, returns an empty 
-- list/table if the file does not exist
function lines_from(file)
    if not file_exists(file) then return {} end
    lines = {}
    for line in io.lines(file) do 
      lines[#lines + 1] = line
    end
   return lines
end

local lines = lines_from(map_file)
local in_global_section= false
local sections ={}

profile = io.open ("proflist_generated.asm","w")
profile:write("//****************************************************************************************\n")
profile:write("// This is automaticly generated asm-file by generate_proflist.bat (generate_proflist.tcl \n")
profile:write("// Use this script to parse map-file to extract functions from abs-file \n")
profile:write("// and to generate initial asm-template for profiling.\n")
profile:write("// It is recommended to remove  all unnecessary functions to make profiling more precise.\n")
profile:write("//****************************************************************************************\n")
profile:write("import from profiler.mlb;\n")
profile:write("\n")
profile:write("PROFILE_BEGIN(16);\n")
profile:write("\n")


for k,v in pairs(lines) do
	-- collect all .text*** sections => sections[] 
	if string.match(v,'.text') then
		local it = v:gmatch("%S+")
		local section = {name=it(),	start=it(),size=it()}
		if not has_element(section.name,exclude_sections) then 
			table.insert(sections,section)
		end
	end
  
	if string.match(v,'GLOBAL SYMBOLS:') then
		in_global_section = true
		goto continue
	end
  
	if string.match(v,'LOCAL SYMBOLS:') then
		break
	end

	if not string.match(v,'0x') then
		goto continue
	end
  
	if in_global_section then 
		local it = v:gmatch("%S+")
		local label = {name=it(),addr=it()}
		for i,section in pairs(sections) do
			if ((label.addr>= section.start) and (label.addr +0 < section.start+section.size)) then
			--section_end = section.start + section.size
			--print ("end=",section_end)
			--if label.addr < (section.start + section.size)  then
			--print(label.name, label.addr, section.name, section.start, section.size)
			if not has_prefix(label.name, exclude_prefixes) then
				if not has_element(label.name, exclude_funcs) then
					if has_element(label.name, nonstd_funcs) then
						profile:write("\tPROFILE_NONSTD_FUNC(",label.name,', "',label.name,"\");\n")
					else
						profile:write("\tPROFILE_FUNC(",label.name,', "',label.name,"\");\n")
					end
				end
			end
			--i  = section.start + section.size
			end
		end
		
  end
  ::continue::
end

profile:write("PROFILE_END();\n")
profile:close()

