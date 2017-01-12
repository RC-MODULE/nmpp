-- https://github.com/LuaDist/luaxml
require('LuaXML')

--vara = {}
--print( xml.str(vara, 'indent', 'tag'))
-- <?xml-stylesheet type='text/xsl' href='nmpp.xsl'?>


-- Doxygen function xml-parser 
-- http://stackoverflow.com/questions/17707777/luaxml-parse-the-xml-with-multiple-tags-with-the-same-name

function exists(func,list)
	for i=1,#list do
		if func==list[i] then
			return true
		end
	end
	return false
end

function scan_doxy_xml(xml_file)
	print('[scanning]: '..xml_file)
	local funcs = {}
	-- load XML data from file xml_file into local table xfile
	local xfile = xml.load(xml_file)
	-- search for substatement having the tag "sectiondef"
	local findex=1
	local compounddef=xfile:find("compounddef")
	if    compounddef then
		for c=1,#compounddef do
			local element = compounddef[c] 
			local sectiondef = element:find("sectiondef")
			if    sectiondef then 
				--print('[SCAN]..'..#sectiondef)
				for i=1, #sectiondef do
					local element=sectiondef[i]
					if    element[0]=='memberdef' then
						local memberdef=sectiondef[i]
						if memberdef.kind=="function" then
							found= memberdef:find("name")[1]
							--if exists(found,funcs) then
							--else
								--print(found)
							funcs[findex]=found
							findex = findex+1
							--end
						end
					end
				end 
			end 
		end
	end
	return funcs
end


-- Lua implementation of PHP scandir function
-- http://stackoverflow.com/questions/5303174/how-to-get-list-of-directories-in-lua
function scandir(directory)
    local i, t, popen = 0, {}, io.popen
    local pfile = popen('ls -a "'..directory..'"')
    for filename in pfile:lines() do
        i = i + 1
        t[i] = filename
    end
    pfile:close()
    return t
end


function scan_doxy_dir(dir)
	local dirlist = scandir(dir)
	local all_funcs={}
	for i,fxml in pairs(dirlist) do
		if  fxml:find(".xml") then
			
			local funcs = scan_doxy_xml(dir..'/'..fxml)
			for i=1,#funcs do
				if not exists(funcs[i],all_funcs) then
					all_funcs[#all_funcs+1] = funcs[i]
				end
			end
		end
	end
	return all_funcs
end

function print_tbl(tbl)
	for i=1,#tbl do
		print(tbl[i])
	end
end 

function doxy_summary(xml_dir,name)
	funcs=	scan_doxy_dir(xml_dir)
	print_tbl(funcs)	

	xnmpp = xml.new('library')
	
	for i=1,#funcs do
		x=xnmpp:append('func')
		x.name=funcs[i]
		x.test="ok"
	end
	xml.save(xnmpp,name..'.xml')


	file = io.open(name..'.xml', "rt") -- r read mode and b binary mode
	content = file:read("*a") -- *a or *all reads the whole file
	file:close()

	file = io.open(name..'.xml', "wt") -- r read mode and b binary mode
	file:write('<?xml-stylesheet type="text/xsl" href="'..name..'.xsl"?>')
	file:write("\n")
	file:write(content) -- *a or *all reads the whole file
	file:close()
end

doxy_summary("d:/GIT/nmpp/make/doxy/xml","nmpp");
doxy_summary("d:/GIT/nmpp/make/doxy/xml_ipp","ipp");
--scan_doxy_xml('xml_ipp/ipp_8h.xml')



print("---\nREADY.")
