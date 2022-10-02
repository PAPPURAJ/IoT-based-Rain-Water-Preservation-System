package com.blogspot.rajbtc.rainwaterpreservation;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.CompoundButton;
import android.widget.ScrollView;
import android.widget.Switch;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import pl.droidsonroids.gif.GifImageView;

public class MainActivity extends AppCompatActivity {

    private  String log="";
    private GifImageView gifImageView;
    private TextView textView;
    private Switch aSwitch;
    private ScrollView scrollView;


    DatabaseReference firebaseDB=FirebaseDatabase.getInstance().getReference("Data");


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        gifImageView=findViewById(R.id.imageView);
        textView=findViewById(R.id.textView);
        aSwitch=findViewById(R.id._switch);
        scrollView=findViewById(R.id.myScrollView);

//        scrollView.post(new Runnable() {
//            @Override
//            public void run() {
//                scrollView.scrollTo(textView.getRight(), textView.getTop());
//            }
//        });


        addLog("Initializing...");

        aSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                firebaseDB.child("Manual").setValue(isChecked?"1":"0");
                addLog("Manually turned "+(isChecked?"on":"off"+"!"));
            }
        });

        firebaseDB.child("Mode").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                switch (snapshot.getValue(String.class)){
                    case "0":
                        gifImageView.setImageResource(R.drawable.rain);
                        addLog("No rain is detected!");
                        break;
                    case "1":
                        gifImageView.setImageResource(R.drawable.rain_tree);
                        addLog("Water is using for normal use!");
                        break;

                    case "2":
                        gifImageView.setImageResource(R.drawable.rain_tank);
                        addLog("Water is preserving!");
                        break;



                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });


    }


    void addLog(String log){
        this.log=this.log+log+"\n";
        textView.setText(this.log);
        scrollView.smoothScrollTo(textView.getLeft(),textView.getBottom());
    }
}