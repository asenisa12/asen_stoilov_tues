
require "csv"
valuta=ARGV[1].to_s
all=Array.new()
CSV.foreach(ARGV[0],"r") do |row|
if row[4].to_s.include? valuta
all<<[row[0],row[1],row[2].to_i,row[3],row[4],row[5]]
end
end
p all[1]
CSV.open("#{ARGV[0].chomp('.csv')}_result","w") do |csv|
all.sort_by{|a,b,c,d,e,f| c}.each do |l|
 csv<< l
 end
 end

