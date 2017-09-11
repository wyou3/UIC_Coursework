import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Comparator;

public class city implements Comparable<city>{
	public String name;
	public int vertex;   //vertex number or city number
	
	public int average; 	//used in Dijkstra's
	public int distance;    //used in Dijkstra's 
	public boolean checked; //used in Dijkstra's
	
	public ArrayList<Integer> neighbors = new ArrayList<Integer>();
	public ArrayList<Integer> distances = new ArrayList<Integer>();
	public static int numCities = 0;
	
	public city(String name, int vertex){
		this.name = name;
		this.vertex = vertex;
		numCities++;
	}
	
	public void addNeigbor(int vertex, int distance){
		neighbors.add(vertex);
		distances.add(distance);
	}
	
	public void printList(){
		System.out.print((vertex+1) + "	  ");
		for(int n: neighbors)
			System.out.print((n+1) +" ");
		System.out.println();
	}
	
	public void sortNeightbors(){
	     boolean flag = true;  
	     int temp1,temp2;   

	     while(flag)
	     {
	     	flag= false;    
	     	for(int i=0; i<neighbors.size()-1; i++)
	     	{
	     		if ( distances.get(i) < distances.get(i+1))  
	            {
	            	temp1 = neighbors.get(i);  
                    temp2 = distances.get(i);
                    neighbors.set(i, neighbors.get(i+1));
                    distances.set(i, distances.get(i+1));
                    neighbors.set(i+1, temp1);
                    distances.set(i+1, temp2);
                    flag = true;             
	            } 
	        } 
	    } 
	}

	@Override
	public int compareTo(city c2) {
		return name.compareTo(c2.name);
	}
	
	public static Comparator<city> cityVertexComparator
    = new Comparator<city>() {
		public int compare(city c1, city c2) {
			//ascending order
			return c1.vertex - c2.vertex;
		}
	};
	
	public static Comparator<city> cityAverageComparator
    = new Comparator<city>() {
		public int compare(city c1, city c2) {
			//ascending order
			return c1.average - c2.average;
		}
	};

}
