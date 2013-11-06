require "date"
require "csv"
date1=Date.parse(ARGV[1])
date2=Date.parse(ARGV[2])
all=Array.new()

CSV.foreach(ARGV[0],"r") do |row|
p row[2]
if Date.parse(row[2].to_s)>date1 && Date.parse(row[2].to_s)<date2 
 if row[3].to_i==1
 all<<[row[0],row[1],row[2]]
 end
end
end
CSV.open("#{ARGV[0].chomp('.csv')}_result","w") do |csv|
all.sort_by{|a,b,c| c}.each do |l|
 csv<<l
 end
end
