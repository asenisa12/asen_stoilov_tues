require "csv"

arr = []
age = ARGV[1].to_i
CSV.foreach(ARGV[0], "r") do |row|
	a =row[1].to_i

	if (a+2 >= age || a-2 <= age)
	p "s" 
		if (row[3].to_s).include? "Sama"
			arr << row
		end
	end
end

arr = arr.sort_by! {|e| [e[0].to_s]}

CSV.open("girls_result.csv", "w") do |csv|
	arr.each do |l|
		csv << l
	end
end
