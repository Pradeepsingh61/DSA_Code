import java.util.HashMap;
import java.util.Scanner;

public class Anagram {
    public static boolean validanagram(String s1,String s2){
        if(s1.length()!=s2.length()){
            return false;
        }
        HashMap<Character,Integer>hm=new HashMap<>();
        for(int i=0;i<s1.length();i++){
            hm.put(s1.charAt(i),hm.getOrDefault(s1.charAt(i),0)+1);
        }
        for(int i=0;i<s2.length();i++){
            char c=s2.charAt(i);
            if(hm.get(c)!=null){
                if(hm.get(c)==1){
                    hm.remove(c);
                }
                else{
                    hm.put(c,hm.get(c)-1);
                }
            }
            else{
                return false;
            }
        }
        return hm.isEmpty();
    }

    public static void main(String[] args) {
        
        String s1="CAR";
        String s2="RAC";
        System.out.println(validanagram(s1,s2));
    }
}
