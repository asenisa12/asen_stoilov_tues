require "csv"

clas = ARGV[1].to_s
arr = []
CSV.foreach(ARGV[0], "r") do |row|
	if clas==row[1]
		arr << row
	end 
end

File.open("result12.csv" , "w") do |csv|
	arr.each do |l|
		csv << l
	end	
end
