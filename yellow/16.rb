require "csv"
arg = ARGV[1]
arr = []

CSV.foreach(ARGV[0], "r") do |row|
	if row.count(arg) > 0
		arr << row
	end
end

arr.sort_by! {|e| [Date.parse(e[1])]}

CSV.open("#{ARGV[2]}.csv", "w") do |csv|
	arr.each do |l|
		csv << l
	end
end


