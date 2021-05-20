package ucv.edu;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;



public class Main {

	public static void main(String[] args) {
		String[] KEYS = {"K", "KE", "KEY", "KEYA", "KEYAB", "KEYABC", "KEYABCD"};
		String[] TEXTS = {"Ana a cumparat mai multe mere.",
						  "Maria nu a mers la scoala azi."};
		// TODO Auto-generated method stub
		ExecutorService executors = Executors.newFixedThreadPool(8);
		System.out.println(TEXTS[0].length());
		
		int i = 0;
		for(String s : KEYS)
		{
			executors.execute(new VigenereCypher(i, s, TEXTS[0]));
			i++;
		}
		executors.shutdown();
		
		System.out.println("----------------------------");
		
		i = 0;
        ExecutorService exService = Executors.newFixedThreadPool(8);
        System.out.println(KEYS[4].length());
        StringBuilder stringBuilder = new StringBuilder();
        
        for(String s : TEXTS)
        {
        	stringBuilder.append(s);
        	System.out.println(stringBuilder.length());
        	exService.execute(new VigenereCypher(i, KEYS[4], stringBuilder.toString()));
        	i++;
        }
        exService.shutdown();
	}
	

}
