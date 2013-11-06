require "csv"

all=Hash.new() 
CSV.foreach(ARGV[0],"r") do |row|
val=row[4].split(" ")
if val[0].length==3
all[val[0]]+= row[2].to_i
end
end



CSV.open("#{ARGV[0].chomp('.csv')}_result4.csv","w") do |csv|
all.each do |l|
csv<< l
end
end
