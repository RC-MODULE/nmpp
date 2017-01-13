-- https://github.com/LuaDist/luaxml
require('LuaXML')

function print_tbl(tbl)
	for i=1,#tbl do
		print(tbl[i])
	end
end 

function read_xml(xml_file)
	print('[scanning]: '..xml_file)
	local funcs = {}
	-- load XML data from file xml_file into local table xfile
	local xfile = xml.load(xml_file)
	-- search for substatement having the tag "sectiondef"
	local findex=1
	local library=xfile:find("library")
	if    library then
		for f=1,#library do
			local func = library[f] 
			funcs[f]=func
		end
	end
	return funcs
end

nmpp= read_xml('nmpp.xml')
ipp = read_xml('ipp.xml')

--print_tbl(ipp)
-- print_tbl(nmpp)
xipp = xml.new('library')
for i=1,#ipp do
	local ipp_func_name=string.gsub(ipp[i].name,"ipp","nmpp")
	--print (ipp_func)
	x=xipp:append('func')
	x.id=i
	--x.analog=""
	x.name=ipp[i].name
	for n=1,#nmpp do
		local nmpp_func=nmpp[n]
		at = string.find(ipp_func_name,nmpp_func.name..'_')
		if ipp_func_name==nmpp_func.name or at==1 then
			--print(ipp_func_name,nmpp_func.name)
			x.analog=nmpp[n].name
		end
	end
end

xml.save(xipp,'ipp-nmpp.xml')
--print ( xml.eval('<func name="SCL_DivC" test="ok" />'))
--d=xml.eval('<func name="SCL_DivC" test="ok" />')
-- print(nmpp[1].test)
--d=xml.eval(nmpp[1]) -- '<func name="SCL_DivC" test="ok" />')
--print(d.test)
--print ( xml.eval(nmpp[1]))

--print_tbl(nmpp)

--arr={{["x"]=1,1,1},{2,2,2},{3}}

--print(arr[2]['x'])


print("---\nREADY.")
