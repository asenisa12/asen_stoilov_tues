require "csv"
arr = []
CSV.foreach(ARGV[0], "r") do |row|
	
	arr << row
end

arr = arr.sort_by! {|a| [a[0].to_i, a[1].to_i] }.reverse
arr = arr.take(5)
arr = arr.sort_by! {|a| [a[0].to_i, a[1].to_i] }.reverse
CSV.open("123.csv","w") do |csv|
	arr.each do  |l| 
		csv << l
	end 
end
