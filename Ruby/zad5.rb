require "csv"
all=Array.new()
CSV.foreach(ARGV[0],"r") do |row|
if row[2].to_f > ARGV[1].to_f 
 all<<[row[0],row[1],row[2].to_i,row[3],row[4],row[5]]
 end
end

CSV.open("#{ARGV[0].chomp('.csv')}_result5.csv","w") do |csv|
 all.sort_by{|a,b,c,d,e,f| c}.reverse.each do |l|
 csv<< l
 end
end 
