package com.example.nmaha.es;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;


//import android.support.v7.app.AppCompatActivity;
import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
//import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Timer;
import java.util.TimerTask;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Timer;
import java.util.TimerTask;

import static com.example.nmaha.es.R.id.LDR;
import static com.example.nmaha.es.R.id.POT;

public class MainActivity extends AppCompatActivity {
    // public static int i=0;
    private TextView ldr;
    private TextView pot;
    public void auto(){
        final long period = 10;
        new Timer().schedule(new TimerTask() {
            @Override
            public void run() {
                // do your task here
                new JSONTask().execute("https://api.thingspeak.com/channels/378665/fields/1.json?api_key=BEK2F6TLAGBORNR1","field1");
                new JSONTask1().execute("https://api.thingspeak.com/channels/378665/fields/2.json?api_key=BEK2F6TLAGBORNR1","field2");
            }
        }, 0, period);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ldr = (TextView)findViewById(R.id.LDR);
        pot = (TextView)findViewById(R.id.POT);
        auto();

    }
    class JSONTask extends AsyncTask<String,String,String>{
        @Override
        protected  String doInBackground(String... params ){
            StringBuffer buffer=new StringBuffer();
            HttpURLConnection connection=null;
            BufferedReader reader=null;
            URL url= null;
            try {
                url = new URL(params[0]);

                connection=(HttpURLConnection)url.openConnection();
                connection.connect();

                InputStream stream=connection.getInputStream();
                reader=new BufferedReader(new InputStreamReader(stream));
                String line="";
                buffer=new StringBuffer();
                while ((line=reader.readLine())!=null){
                    buffer.append(line);
                }
                String finalJson=buffer.toString();
                JSONObject parentobject=new JSONObject(finalJson);
                JSONArray parentarray=parentobject.getJSONArray("feeds");
                int i=parentarray.length()-1;

                JSONObject finalobject=  parentarray.getJSONObject(i);
                String val=finalobject.getString("field1");

                Log.d("LDR", val);
                return val;
            } catch (IOException e) {
                e.printStackTrace();
            } catch (JSONException e) {
                e.printStackTrace();
            }
            return null;
        }


        @Override
        protected void onPostExecute(String result){
            super.onPostExecute(result);
            ldr.setText("LDR:"+result);

        }
    }
    class JSONTask1 extends AsyncTask<String,String,String>{
        @Override
        protected  String doInBackground(String... params ){
            StringBuffer buffer=new StringBuffer();
            HttpURLConnection connection=null;
            BufferedReader reader=null;
            URL url= null;
            try {
                url = new URL(params[0]);

                connection=(HttpURLConnection)url.openConnection();
                connection.connect();

                InputStream stream=connection.getInputStream();
                reader=new BufferedReader(new InputStreamReader(stream));
                String line="";
                buffer=new StringBuffer();
                while ((line=reader.readLine())!=null){
                    buffer.append(line);
                }
                String finalJson=buffer.toString();
                JSONObject parentobject=new JSONObject(finalJson);
                JSONArray parentarray=parentobject.getJSONArray("feeds");
                int i=parentarray.length()-1;

                JSONObject finalobject=  parentarray.getJSONObject(i);
                String val=finalobject.getString("field2");

                Log.d("POT", val);
                return val;
            } catch (IOException e) {
                e.printStackTrace();
            } catch (JSONException e) {
                e.printStackTrace();
            }
            return null;
        }


        @Override
        protected void onPostExecute(String result){
            super.onPostExecute(result);
            pot.setText("POT:"+result);

        }
    }
}