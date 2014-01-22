require "csv"


def crname(row)
	name = ((row.split("_")).drop(1)).join(" ")
	return name 
end
arr=[]
CSV.foreach(ARGV[0],"r") do |row|
	if (row[1].include? ARGV[1])== false
		arr << [crname(row[0]),row[3]]
	end
end

arr = arr.sort_by! {|e| [e[1].to_i]}.reverse

CSV.open("#{ARGV[0].chomp('.csv')}_result2.csv", "w") do |csv|
	arr.each do |l|
		csv << l
	end
end
