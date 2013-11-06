require "date"
require "csv"
 all =Array.new()
 name=ARGV[1].to_s
 mach=String.new()
 
 CSV.foreach(ARGV[0],"r") do |row|
 if row[0].to_s.include? name or row[2].to_s.include? name
 mach=row[0].to_s+" "+row[1].to_s+" "+row[2].to_s+" "+row[3].to_s
 date=Date.parse(row[4])
 date=date.strftime('%d/%m/%Y')
  all<<[mach,date]
  end

 end
p all[0]

 CSV.open("#{ARGV[0].chomp('.csv')}_result.csv","w") do |csv|
 all.sort_by{|a,b| b}.each do |l|
 csv<<l
 end
 end
