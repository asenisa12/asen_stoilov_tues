require "date"
require "csv"
ftime=""
stime=""
ltime=""

time = ""

f=""
s=""
l=""
t=""
def create_name(row)
	name = row.split("_")
	name = name.drop(1)
	name = name.join(" ")	
	return name 
end

arr = []
CSV.foreach(ARGV[0], "r") do |row|
	t=((row[2].split("_"))[1]).to_s
	if ftime == ""
		ftime = t
	end
	if stime == ""
		stime = t
	end
	if ltime == ""
		ltime = t
	end
	if Date.parse(t) < Date.parse(ftime)
		f = t,create_name(row[0])
		ftime = t
	end
	if Date.parse(t) < Date.parse(stime) && Date.parse(t)>Date.parse(ftime)
		s = t,create_name(row[0])
		stime = t
	end
	if Date.parse(t) > Date.parse(ltime)
		l = t,create_name(row[0])
		ltime = t
	end
end
arr << l
arr << s
arr << f

arr.sort_by! {|e| [e[1].to_s]}

CSV.open("#{ARGV[0].chomp('.csv')}_result.csv", "w") do |csv|
	arr.each do |l|
		csv << l
	end
end
