//This file cleans the data and seperates out individual skills

package dataclean;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jblas.DoubleMatrix;
import org.jblas.Singular;
import org.json.JSONArray;
import org.json.JSONObject;

public class cd 
{
    public String readFile(String FilePath)
    {
        BufferedReader br = null;
	FileReader fr = null;
        String out = "";
        try 
        {

            fr = new FileReader(FilePath);
            br = new BufferedReader(fr);

            
            String sCurrentLine;

            br = new BufferedReader(new FileReader(FilePath));

            while ((sCurrentLine = br.readLine()) != null) {
                out += sCurrentLine;
            }

	} 
        catch (IOException e) 
        {
            e.printStackTrace();

        }
        finally 
        {
            try 
            {
                if (br != null)
                    br.close();

		if (fr != null)
                    fr.close();

            } catch (IOException ex) 
            {

                ex.printStackTrace();

            }

        }
        return out;
    }
    
    public String[] getFileName(String path)
    {
        File folder = new File(path);
        return folder.list();
    }
    
    public void composeFile(String path)
    {
        String data;
        String[] file = getFileName(path);
        List<JSONObject> objs = new ArrayList<>();
        JSONArray myArray = new JSONArray();
        
        for(int i = 0 ; i < file.length ; i++)
        {
            data = readFile(path + file[i]);
            
            
            JSONObject jsonObj = new JSONObject(data);
            JSONArray jsonArray = jsonObj.getJSONArray("Candidates");
            int size =  jsonArray.length();
            for (int j = 0 ; j < size ; j++)
            {
                JSONObject candidate = jsonArray.getJSONObject(j);
                candidate.put("file", file[i]);
                objs.add(candidate);
                myArray.put(candidate);
            }
        }
        
        JSONObject myCan = new JSONObject();
        myCan.put("Candidates", myArray);
        
        writeObj(myCan, "CandidatesAll.txt");
    }
    
    
    
        
    public int getSize(JSONObject obj)
    {
        JSONArray arr = obj.getJSONArray("Candidates");
        return arr.length();
    }
    
    public String getData(JSONObject obj, String key, int index)
    {
        JSONArray arr = obj.getJSONArray("Candidates");
        JSONObject myCan = arr.getJSONObject(index);
        return myCan.getString(key);
    }
    
    public ArrayList<String> generateSeperator(String attr, JSONObject json)
    {
        String[] spt = new String[]{"&&", "," , "|", ";", ".", "\n", "\u2022", "\uf0d8", "\u25a1", "\u002a", "\u27a2"};
        String data, data1="";
        ArrayList<String> coll = new ArrayList<>();
        for (int j = 0 ; j < this.getSize(json) ; j++)
        {
            data = getData(json, attr, j);
            for (int i = 0 ; i < spt.length ; i++ )
            {
                data = data.replace(spt[i], ",");
            }
            String[] parts = data.split(",");
            
            for (int i = 0 ; i < parts.length; i++)
            {
                
                if(!coll.contains(parts[i].trim()))
                {
                    coll.add(parts[i].trim());
                }
            }
            
        }
        return coll;
    }
    
    public void saveFile(String data, String path)
    {
        try {
                File file = new File(path);
                FileWriter fileWriter = new FileWriter(file);
                fileWriter.write(data);
                fileWriter.flush();
                fileWriter.close();
        } catch (IOException e) 
        {
            e.printStackTrace();
        }
    }
    
    public void generateCSV(String[] files, JSONObject can)
    {
        for(String file: files)
        {
            String out = "";
            //ArrayList<String> job = obj.generateSeperator("Job-Title", can);
            ArrayList<String> job = generateSeperator(file, can);
            //String[] idList = job.toString();
            for(int i = 0 ; i < job.size() ; i++)
            {
                out += job.get(i) + "\n";
            }
            saveFile(out, file+".csv");

        }
    }
    
    public boolean[][] generateMatrix(ArrayList<String> atr, String name, JSONObject obj)
    {
        int userSize = getSize(obj), atrSize = atr.size();
        String data;
        boolean [][]out = new boolean[userSize][atrSize];
        for(int i = 0 ; i < userSize ; i++)
        {
            data = getData(obj, name, i);
            data = " " + data + " ";
            for (int j = 0 ; j < atrSize ; j++)
            {
                if(data.contains(" "+ atr.get(j) +" "))
                {
                    out[i][j] = true;
                }
            }
        }
        return out;
    }
    
    public void generateCSVfrom2d(boolean[][] arr, String path)
    {
       
        try {
            File file = new File(path);
            FileWriter fileWriter = new FileWriter(file);
            
            
            int temp = arr.length;
            int temp1 = arr[0].length;
            boolean[][] myArr = arr;
            for(int i = 0 ; i < temp ; i++)
            {
                System.out.println("User" + i);
                for(int j = 0 ; j < temp1-1 ; j++)
                {
                    fileWriter.write((myArr[i][j]?"1":"0") + ",");
                }
                fileWriter.write(myArr[i][temp1-1]?"1":"0" + "\n");
            }
            
            fileWriter.flush();
            fileWriter.close();
        } catch (IOException e) 
        {
            e.printStackTrace();
        }
        
    }
    
    
}
