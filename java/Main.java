package belt2;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		ArrayList<Chart> list = new ArrayList<Chart>();
		Scanner sc = new Scanner(System.in);
		boolean chet = true;
		String vale;
		while(true)
		{
			vale=sc.next();
			if (vale.equals("a")){
				break;
			}
			if (chet){
				int val = Integer.parseInt(vale); 
				PieChart p = new PieChart(val*2,val*4);
				list.add(p);
			}else {
				int val = Integer.parseInt(vale); 
				BarChart b = new BarChart(val*3,val*5);
				list.add(b);
			}
			chet=false;
		}
		
		for (Chart c: list)
		{
			System.out.println(c.getValue1());
			System.out.println(c.getValue2());
		}
		
		for (Chart c: list)
		{
			if (c instanceof BarChart)
			{
				((BarChart)c).asen();
			}
		}

		for (Chart c: list)
		{
			System.out.println(c.getValue1()+c.getValue2());
		}
	}

}
