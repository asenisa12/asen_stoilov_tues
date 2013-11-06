require "csv"
require "date"
all=Array.new()
CSV.foreach(ARGV[0],"r") do |row|
if Date.parse(row[1])<Date.parse(ARGV[1])
 all<<[row[0],row[1],row[2].to_i,row[3],row[4],row[5]]
 end 
end
CSV.open("#{ARGV[0].chomp('.csv')}_result6.csv","w") do |csv|
all.sort_by{|a,b,c,d,e,f| c}.reverse.each do |l|
csv<< l
end
end
