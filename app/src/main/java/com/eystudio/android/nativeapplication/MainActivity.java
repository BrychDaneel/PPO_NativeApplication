package com.eystudio.android.nativeapplication;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.IOException;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    private static final int GALLERY_REQUEST = 1;

    ImageView imageView;
    Button selectButton;
    Button processButton;

    Bitmap bitmap;

    private void getElements(){
        imageView = (ImageView) findViewById(R.id.picture);
        selectButton = (Button) findViewById(R.id.btn_select);
        processButton = (Button) findViewById(R.id.btn_process);
    }

    private void bind(){
        selectButton.setOnClickListener(this);
        processButton.setOnClickListener(this);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getElements();
        bind();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native int[] processImage(int [] pixels, int width, int height);

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private void process(){
        if (bitmap == null)
            return;
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();
        int[] pixels = new int[width * height];
        bitmap.getPixels(pixels, 0, width, 0, 0, width, height);
        int[] newPixels = processImage(pixels, width, height);
        bitmap = Bitmap.createBitmap(newPixels, width, height, Bitmap.Config.ARGB_4444);
        imageView.setImageBitmap(bitmap);
    }

    private void select(){
        Intent photoPickerIntent = new Intent(Intent.ACTION_PICK);
        photoPickerIntent.setType("image/*");
        startActivityForResult(photoPickerIntent, GALLERY_REQUEST);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == GALLERY_REQUEST && resultCode == RESULT_OK){
            Uri selectedImage = data.getData();
            try {
                bitmap = MediaStore.Images.Media.getBitmap(getContentResolver(), selectedImage);
            } catch (IOException e) {
                bitmap = null;
                return;
            }
            imageView.setImageBitmap(bitmap);
        } else
            super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()){
            case R.id.btn_process: process(); break;
            case R.id.btn_select: select(); break;
        }
    }
}
