require "csv"
require "date"
big = ""
small = ""
bdate = ""
sdate = ""
 
t = ""


def create_name(row)
	name = row.split("_")
	name = name.drop(1)
	name = name.join(" ")	
	return name 
end


CSV.foreach(ARGV[0], "r") do |row|
	t = row[2].slice(5,10)
	t = t.split("-")
	if bdate == ""
		bdate = Time.new(t[0],t[1],t[2])
	end
	if sdate == ""
		sdate = Time.new(t[0],t[1],t[2])
	end
	if bdate < Time.new(t[0],t[1],t[2])
		big = create_name(row[0]),t.join("-") 
		bdate = Time.new(t[0],t[1],t[2])
	end
	
	if sdate > Time.new(t[0],t[1],t[2])
		
		small = create_name(row[0]),t.join("-") 
		sdate = Time.new(t[0],t[1],t[2])
	end
	
	
end
 
 
 CSV.open("result4.csv","w") do |csv|
 	csv << big
 	csv << small
 end

