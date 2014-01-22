require "csv"
arr = []
CSV.foreach(ARGV[0], "r") do |row|
	if row[1].casecmp(ARGV[1]) == 0
		arr << row
	end
end

arr.sort_by! {|e| [e[2].to_i]}

CSV.open("125.csv","w") do |csv|
	arr.each do |l|
		csv << l
	end
end
