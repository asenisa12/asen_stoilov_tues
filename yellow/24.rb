require "csv"

res = ARGV[1].to_i
num = ARGV[2].to_i
arr = []
CSV.foreach(ARGV[0], "r") do |row|
	if res > row[1].to_i
		arr << row
	end
end

arr = (arr.sort_by! {|e| [e[3].to_i]}).take(num)

CSV.open("top.csv", "w") do |csv|
	arr.each do |l|
		csv << l
	end
end
