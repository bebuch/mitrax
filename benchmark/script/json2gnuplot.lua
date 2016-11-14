DIR = debug.getinfo(1).source:match("@(.*)json2gnuplot.lua$")
JSON = (loadfile (DIR .. "JSON.lua"))() -- one-time load of the routines

local filename = arg[1]

function readAll(file)
	local f = io.open(file, "rb")
	local content = f:read("*all")
	f:close()
	return content
end

function string.ends(String,End)
	return End=='' or string.sub(String,-string.len(End))==End
end

local json_data = readAll(filename)
local data = JSON:decode(json_data) -- decode example

local div = 1000000
local min = 0
local max = 0
local mean = 0
local stddev = 0
local last_name = ""
local line = 0
local more_than_one = false
print("#line", "name", "mean", "stddev-min", "min", "max", "stddev-max")
for i, v in ipairs(data.benchmarks) do
	if string.ends(v.name, "_stddev") then
		more_than_one = true
		break;
	end
end

for i, v in ipairs(data.benchmarks) do
	if v.name == last_name then
		min = math.min(min, v.real_time)
		max = math.max(max, v.real_time)
	elseif string.ends(v.name, "_mean") then
		mean = v.real_time
	elseif string.ends(v.name, "_stddev") then
		stddev = v.real_time
		line = line + 1
		print(line, last_name, mean / div, (mean - stddev) / div, min / div, max / div, (mean + stddev) / div)
	else
		min = v.real_time
		max = v.real_time
		last_name = v.name
		if not more_than_one then
			line = line + 1
			print(line, last_name, v.real_time / div, v.real_time / div, min / div, max / div, v.real_time / div)
		end
	end
end
