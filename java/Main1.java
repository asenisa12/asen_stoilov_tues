package belt1;

import java.util.ArrayList;
import java.util.Scanner;

public class Main 
{
	
	public static void main(String[] args) 
	{
		ArrayList<Chart> charts = new ArrayList<Chart>();
		Scanner sc = new Scanner(System.in);
		String[] cons;
		
		while(true)
		{
			cons = sc.next().split(",");
			if (cons.length == 1) 
				break;
			
			if (cons[3].equals("p"))
			{
				int i1 = Integer.parseInt(cons[0]);
				int i2 = Integer.parseInt(cons[1]);
				int i3 = Integer.parseInt(cons[2]);
				PieChart p = new PieChart(i1,i2,i3);
				charts.add(p);
			}
			if (cons[3].equals("b"))
			{
				int i1 = Integer.parseInt(cons[0]);
				int i2 = Integer.parseInt(cons[1]);
				int i3 = Integer.parseInt(cons[2]);
				BarChart b = new BarChart(i1,i2,i3);
				charts.add(b);
			}
		}
	
		for (Chart c: charts){
			if (c instanceof PieChart){
				if (c.getValue2()>c.getValue1()){
					((PieChart)c).asen();
				}
			}
		}
		
        for(Chart c: charts){
            System.out.println(c.getValue1());
            System.out.println(c.getValue2());
            System.out.println(c.getValue3());
        }
	}
	
	

}
