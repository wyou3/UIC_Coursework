//woong jin you
//wyou3
//CS342 program 1

import java.io.*;
import java.util.Arrays;

public class citySearch {
	
	public static void main(String[] args){
		String fileName = "CityNames.txt";
		String line = null;
		city[] cities = null;
		int numCities;
		int i = 0;
		
		// reading in City Names file
		try{
			FileReader fileReader = new FileReader(fileName);
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			
			line = bufferedReader.readLine();
			numCities = Integer.parseInt(line);
			
			cities = new city[numCities];
			
			i = 0;
			while(i < numCities && (line = bufferedReader.readLine()) != null){
				cities[i] = new city(line, i);
				i++;
			}
			
			bufferedReader.close();
		}catch(FileNotFoundException ex){
			System.out.println(
					"Unable to open file '" + 
					fileName + "'");
		}catch(IOException ex){
			System.out.println(
					"Error reading file '" +
					fileName + "'");
			// or just
			// ex.printStackTrace();
		}
	
		// reading in City Distances file
		fileName = "CityDistances.txt";
		try{
			FileReader fileReader = new FileReader(fileName);
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			String[] tokens;
			int c1, c2, distance; //city1, city2
			
			line = bufferedReader.readLine();
			
			while((line = bufferedReader.readLine()) != null){
				tokens = line.split(" ");
				c1 = Integer.parseInt(tokens[0]) - 1;
				c2 = Integer.parseInt(tokens[1]) - 1;
				distance = Integer.parseInt(tokens[2]);
				cities[c1].addNeigbor(c2, distance);
				cities[c2].addNeigbor(c1, distance);
			}
	
			bufferedReader.close();
		}catch(FileNotFoundException ex){
			System.out.println(
					"Unable to open file '" + 
					fileName + "'");
		}catch(IOException ex){
			System.out.println(
					"Error reading file '" +
					fileName + "'");
			// or just
			// ex.printStackTrace();
		}
		
		printAdjecencyList(cities);	
		dijkstra(58-1, cities);
	    //Arrays.sort(cities);
	    Arrays.sort(cities, city.cityVertexComparator);
	    //print  distances
		System.out.println();
		System.out.println("City:Chicago            Distance from city");
		System.out.println("------------	        ------------------");
		for(i=0; i<city.numCities; i++){
			line = String.format("%1$-30s %2$11s", cities[i].name, cities[i].distance);
			System.out.println(line);
		}
		
		//find and print best fit city
		fileName = "Participants.txt";
		findOptimalCity(fileName, cities);	
	}

	private static void printAdjecencyList(city[] cities) {
		System.out.println( "Vertex     Adjacency List");
		System.out.println( "------     --------------");
		for(int i=0; i<city.numCities; i++)
			cities[i].printList();
	}
	
	private static void dijkstra(int vertex, city[] cities) {
		//sort cities by index
		Arrays.sort(cities, city.cityVertexComparator);
		
		//set all city distances to infinity except initial city
		for(int i=0; i<city.numCities; i++){
			cities[i].distance = Integer.MAX_VALUE;
			cities[i].checked = false;
		}
		
		cities[vertex].distance = 0;
		dijkstra_helper(vertex, cities);
	}

	private static void dijkstra_helper(int vertex, city[] cities) {
		int newDistance = 0;
		int i = 0; //index
		
		cities[vertex].checked = true;
		cities[vertex].sortNeightbors();
		for(int c: cities[vertex].neighbors){
			newDistance = cities[vertex].distances.get(i) + cities[vertex].distance;
			if(cities[c].distance > newDistance)
				cities[c].distance = newDistance;
			i++;
		}
		
		for(int n: cities[vertex].neighbors)
			if(cities[n].checked == false)
				dijkstra_helper(n, cities);
	}
	
	private static void findOptimalCity(String fileName, city[] cities) {
		String line;
		int numParticipants;
		int i = 0;
		
		//reset averages
		for(i=0; i<city.numCities; i++)
			cities[i].average = 0;
			
		try{
			FileReader fileReader = new FileReader(fileName);
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			String[] tokens;
			int cityIndex;
			
			line = bufferedReader.readLine();
			numParticipants = Integer.parseInt(line);
			
			while((line = bufferedReader.readLine()) != null){
				tokens = line.split(" ");
				cityIndex = Integer.parseInt(tokens[1]) - 1;
				dijkstra(cityIndex, cities);
				
				for(int j=0; j<city.numCities; j++)
					cities[j].average += cities[j].distance;
				
				i++;
			}
			
			for(i=0; i<city.numCities; i++){
				cities[i].average = cities[i].average/numParticipants;
			}
			
			Arrays.sort(cities, city.cityAverageComparator);
			
			System.out.println();
			System.out.println("City Chosen: '" + cities[0].name + "'	Average Distance: " + cities[0].average);
			
			bufferedReader.close();
		}catch(FileNotFoundException ex){
			System.out.println(
					"Unable to open file '" + 
					fileName + "'");
		}catch(IOException ex){
			System.out.println(
					"Error reading file '" +
					fileName + "'");
			// or just
			// ex.printStackTrace();
		}
	}
};
