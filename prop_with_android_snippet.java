/**
 * Copyright 2016 FOSSID AB
 * 
 */

package connector;

import java.io.File;
import java.io.FileInputStream;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.Properties;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;

public class connector {
	
	private List<String> AnalizableExtensions;
	public void setAnalizableExtensions(List<String> AnalizableExtensions) { this.AnalizableExtensions = AnalizableExtensions; }
	public List<String> getAnalizableExtensions() { return this.AnalizableExtensions; }
	private String ServerUrl;
	public void setServerUrl(String ServerUrl) { this.ServerUrl = ServerUrl; }
	public String getServerUrl() { return this.ServerUrl; }
	private List<String> DataArray;
	public void setTorixo(List<String> DataArray) { this.DataArray = DataArray; }
	public List<String> getTorixo() { return this.DataArray; }
	private Integer MinLine;
	public void setMinLine(Integer MinLine) { this.MinLine = MinLine; }
	public Integer getMinLine() { return this.MinLine; }
	
	
	public static void main(String[] args) {
		
		System.out.println("connector 1.0. Copyright FOSSID AB 2016.\n");
		String token = String[0];
		String path = String[1];
		
		connector oconnector = new connector();		
				
		try {
			Properties properties = new Properties();
			File currentDirectory = new File(new File(".").getAbsolutePath());
			String oConfigurationFile = currentDirectory.getCanonicalPath() + "/config";
			System.out.println("Reading configuration file: '" + oConfigurationFile + "' ...\n");
			properties.load(new FileInputStream(oConfigurationFile));
			// Configuration file load
			for(String key : properties.stringPropertyNames()) {
				if(Objects.equals(key.toString(), "ANALYZABLE_EXTENSIONS")){					
					String[] extensions = properties.getProperty(key).split(",", -1);
					oconnector.AnalizableExtensions = Arrays.asList(extensions);					
				}	
				if(Objects.equals(key.toString(), "MIN_LINE")){	oconnector.MinLine = Integer.parseInt(properties.getProperty(key)); }
			}
		} catch (Exception e) {
			System.out.println("Error reading configuration file");
		}
					
		try {
			oconnector.WalkPath(path);
		} catch (Exception e) {
			System.out.println("Error reading path.");
		}
		
	}

    /**
     * Reads a single byte from this stream and returns it as an integer in the
     * range from 0 to 255. Returns -1 if the end of the stream has been
     * reached. Blocks until one byte has been read, the end of the source
     * stream is detected or an exception is thrown.
     *
     * @return the byte read or -1 if the end of stream has been reached.
     * @throws IOException
     *             if the stream is closed or another IOException occurs.
     * @since Android 1.5
     */
    public int read() throws IOException {
        byte b[] = new byte[1];
        int ret = mSocket.read(b, 0, 1);
        if (ret == 1) {
            return (int)b[0] & 0xff;
        } else {
            return -1;
        }
    }
	
	/* Walks recursively given path and reads included files. */
	public void WalkPath(String path) {
		try {
			
	        File root = new File(path);
	        File[] list = root.listFiles();

	        if (list == null) return;

	        for (File f : list) {
            	if (f.isDirectory()) {
	            	WalkPath(f.getAbsolutePath());
	                //System.out.println( "\nDirectory:" + f.getAbsoluteFile() );
	            }else{
	            	String fileExtension = getFileExtension(f); //get extension
	            	boolean fileAnalyzable = this.AnalizableExtensions.contains("." + fileExtension.toString()); //check if extension is analyzable
	            	if(fileAnalyzable){
	            		AnalyzeFile(f);
	            		if(!analyzedMD5.isEmpty()){
	            			System.out.println( "analyzable file: (" + analyzedMD5 + ") " + f.getPath() + f.getName());
	            		}	            			            		
	            	}	            	
	            }
	        }			
		} catch (Exception e) {
			System.out.println("Unable to read path ...");
		}
    }
	
	
	public String AnalyzeFile(File file){
		String fileContentMD5 = "";
		String lineMD5 = "";
		String linej64 = "";
		try {
			//Read full File
			Scanner fileScanner = new Scanner(file).useDelimiter("\\Z");
			String fileContent = fileScanner.next();
			fileScanner.close();						
			fileContent.replace(";", "/n").replace("{", "/n").replace("}", "/n").replace("/[ ]{2,}|[\t]/", fileContent);
			fileContentMD5 = MD5(fileContent);
	        
			//Analyze lines
			Scanner lineScanner = new Scanner(file);
			while (lineScanner.hasNext()) {		
				String lineContent = lineScanner.next();
				lineContent.replace(";", "/n").replace("{", "/n").replace("}", "/n").replace("/[ ]{2,}|[\t]/", lineContent);
				lineMD5 = AnalyzeLine(lineContent);
				if(lineMD5 != null){
					
					
				}
		    }
			lineScanner.close();
			//System.out.println(fileContentMD5);
			System.out.println(fileContent);
			Runtime.getRuntime().exit(1);
		} catch ( Exception e ) {
			//System.out.println(e.getMessage());
			// TODO: handle exception
		}
		return null;
	}
	
	
	public String AnalyzeLine(String line){
		try {
			line = line.trim();
			if(line.length() >= this.MinLine){
				String lineMD5 = MD5(line);
				//System.out.println(lineMD5);
				return lineMD5;
			}		
		} catch (Exception e) {
			// TODO: handle exception
		}
		return null;
	}
	
	
	
	
	
	private static String getFileExtension(File file) {
        String fileName = file.getName();
        if(fileName.lastIndexOf(".") != -1 && fileName.lastIndexOf(".") != 0)
        return fileName.substring(fileName.lastIndexOf(".")+1);
        else return "";
    }	
		
	
	
	public void getServerResponse(String urladd){
		try {
			//http://url2parse
			URL url = new URL(urladd);
			BufferedReader br = new BufferedReader(new InputStreamReader(url.openStream()));
			String strTemp = "";
			while (null != (strTemp = br.readLine())) {
				System.out.println(strTemp);
				//return strTemp;
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
	
	
	
	
	public void SaveToLog(String action) {
		try {
			
		} catch (Exception e) {
			System.out.println("Unable to save log ...");
		}
	}
	
}
