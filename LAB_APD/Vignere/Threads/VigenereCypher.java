package ucv.edu;

public class VigenereCypher implements Runnable {
	
	private int id;
	private String key;
	private String text;
	
	public VigenereCypher(int id, String key, String text)
	{
		this.id = id;
		this.key = key;
		this.text = text;
	}
	
	private static String encrypt(String text, final String key)
	{
		StringBuilder result = new StringBuilder();
		
		text = text.toUpperCase();
		
		for(int i = 0, j = 0; i < text.length();i++)
		{
			char ch = text.charAt(i);
			
			if(ch < 'A' || ch > 'Z') 
			{
				result.append(ch);
				continue;
			}
			
			result.append((char) ((ch + key.charAt(j) - 2 * 'A') % 26 + 'A'));
			j = ++j % key.length();
		}
		
		return result.toString();
	}
	
	private static String decrypt(String text, final String key)
	{
		StringBuilder result = new StringBuilder();
		
		text = text.toUpperCase();
		
		for(int i = 0, j = 0; i < text.length(); i++)
		{
			char ch = text.charAt(i);
			
			if(ch < 'A' || ch > 'Z')
			{
				result.append(ch);
				continue;
			}
			
			result.append((char) ((ch - key.charAt(j) + 26) % 26 + 'A'));
			j = ++j % key.length();
		}
		return result.toString();
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		String enc = encrypt(text, key);
		System.out.println(enc);
		System.out.println(decrypt(enc, key));
	}

	
}
