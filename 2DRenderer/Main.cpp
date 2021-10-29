#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"
#include "Process.h"

#include <iostream>
#include <SDL.h>

int main(int, char**)
{
    const int WIDTH = 800;
    const int HEIGHT = 600;

    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
    renderer->Initialize(WIDTH, HEIGHT);

    std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);


    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT: 
            quit = true;
            break;
        }
        framebuffer->Clear({ 0,0,0,0 });

        
        //for (int i = 0; i < 100; i++)
        //{
        //    framebuffer->DrawPoint(rand() % renderer->width, rand() % renderer->height, { 0, 255, 0, 0 });
        //}
        //for (int i = 0; i < 20; i++)
        //{
        //    framebuffer->DrawRect(rand() % renderer->width, rand() % renderer->height, 20, 20, { 0, 0, 255, 0 });
        //}
        //for (int i = 0; i < 20; i++)
        //{
        //    framebuffer->DrawLine(renderer->width >> 1, renderer->height >> 1, rand() % renderer->width, rand() % renderer->height, { 255, 255, 255, 0 });
        //}



        //for (int i = 0; i < 10; i++)
        //{
        //    framebuffer->DrawQuadraticCurve(
        //        rand() % renderer->width, rand() % renderer->height,
        //        rand() % renderer->width, rand() % renderer->height,
        //        rand() % renderer->width, rand() % renderer->height, 30, { 255, 255, 0, 255 });
        //}
        //for (int i = 0; i < 10; i++)
        //{
        //    framebuffer->DrawCubicCurve(
        //        rand() % renderer->width, rand() % renderer->height,
        //        rand() % renderer->width, rand() % renderer->height,
        //        rand() % renderer->width, rand() % renderer->height,
        //        rand() % renderer->width, rand() % renderer->height,
        //        30, { 0, 255, 255, 255 });
        //}


        // Renderer 

        std::unique_ptr<Image> image = std::make_unique<Image>();
        image->Load("../Resources/flower.bmp");
        image->Flip();
        framebuffer->DrawImage(0, 0, image.get());

        std::unique_ptr<Image> image1 = std::make_unique<Image>(*image.get());
        Process::Invert(image1->colorBuffer);
        framebuffer->DrawImage(200, 0, image1.get());

        std::unique_ptr<Image> image2 = std::make_unique<Image>(*image.get());
        Process::Monochrome(image2->colorBuffer);
        framebuffer->DrawImage(400, 0, image2.get());

        std::unique_ptr<Image> image3 = std::make_unique<Image>(*image.get());
        Process::Noise(image3->colorBuffer, 100);
        framebuffer->DrawImage(600, 0, image3.get());

        std::unique_ptr<Image> image4 = std::make_unique<Image>(*image.get());
        Process::Brightness(image4->colorBuffer, -100);
        framebuffer->DrawImage(0, 200, image4.get());

        std::unique_ptr<Image> image5 = std::make_unique<Image>(*image.get());
        Process::ColorBalance(image5->colorBuffer, 0, 0, 100);
        framebuffer->DrawImage(200, 200, image5.get());

        std::unique_ptr<Image> image6 = std::make_unique<Image>(*image.get());
        Process::Threshold(image6->colorBuffer, 200);
        framebuffer->DrawImage(400, 200, image6.get());



        //Render Advanced

        //std::unique_ptr<Image> image = std::make_unique<Image>();
        //image->Load("../Resources/flower.bmp");
        //image->Flip();

        //framebuffer->DrawImage(300, 30, image.get());
       
        //std::unique_ptr<Image> image1 = std::make_unique<Image>(*image.get());
        //Process::BoxBlur(image1->colorBuffer);
        //framebuffer->DrawImage(0, 300, image1.get());

        //std::unique_ptr<Image> image2 = std::make_unique<Image>(*image.get());
        //Process::GaussianBlur(image2->colorBuffer);
        //framebuffer->DrawImage(200, 300, image2.get());

        //std::unique_ptr<Image> image3 = std::make_unique<Image>(*image.get());
        //Process::Sharpen(image3->colorBuffer);
        //framebuffer->DrawImage(400, 300, image3.get());

        //std::unique_ptr<Image> image4 = std::make_unique<Image>(*image.get());
        //Process::Monochrome(image4->colorBuffer);
        //Process::Edge(image4->colorBuffer, 0);
        //framebuffer->DrawImage(600, 300, image4.get());

        framebuffer->Update();

        renderer->CopyBuffer(framebuffer.get());

        renderer->Present();
    }

    SDL_Quit();

    return 0;
}