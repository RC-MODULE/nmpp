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
function str2xml(str)
	local text = string.gsub(str,'<','&lt;')
	text = string.gsub(text,'>','&gt;')
	text = string.gsub(text,'"','&quot;')
	text = string.gsub(text,'&','&amp;')
	return text
end	
									
function scan_doxy_xml(xml_file, names,breifs)
	print('[scanning]: '..xml_file)
	-- local funcs = {}
	-- load XML data from file xml_file into local table xfile
	local xfile = xml.load(xml_file)
	-- search for substatement having the tag "sectiondef"
	-- local findex=1
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
							name = memberdef:find("name")[1]
							if not exists(name,names) then
								names [#names+1]=str2xml(name)
								breif = memberdef:find("briefdescription")[1]
								if breif then 
									breifs[#breifs+1]=str2xml(breif[1])
								else 
									breifs[#breifs+1]=''
								end
							end
						end
					end
				end 
			end 
		end
	end
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


function scan_doxy_dir(dir,names,breifs)
	local dirlist = scandir(dir)
	for i,fxml in pairs(dirlist) do
		if  fxml:find(".xml") then
			scan_doxy_xml(dir..'/'..fxml,names,breifs)
		end
	end
	return all_funcs
end

function print_tbl(tbl)
	for i=1,#tbl do
		print(tbl[i])
	end
end 


function save_xml(var,xml_name,xsl_name)
	if not var then return end
	if not xml_name or #xml_name==0 then return end
	local out = assert(io.open(xml_name, "wb"))
	out:write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
	out:write('<?xml-stylesheet type="text/xsl" href="'..xsl_name..'"?>\n')
	out:write("<!-- file \"",xml_name, "\", generated  by LuaXML -->\n\n")
    out:write(xml.str(var))
    assert(out:close())
end


function doxy_summary(xml_dir,xml_root)
	local names={}
	local breifs={}
	funcs=	scan_doxy_dir(xml_dir,names,breifs)
	--print_tbl(breifs)	

	xnmpp = xml.new('library')
	for i=1,#names do
		x=xnmpp:append('func')
		x.name=names[i]
		x.breif=breifs[i]
		x.test="?"
	end
	--xml.save(xnmpp,xml_root..'.xml')
	save_xml(xnmpp,xml_root..'.xml',xml_root..'.xsl')
end


doxy_summary("d:/GIT/nmpp/make/doxy/xml","nmpp");
doxy_summary("d:/GIT/nmpp/make/doxy/xml_ipp","ipp");
	
print("---\nREADY.")
