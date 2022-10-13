if(boss.Position.x > thresholdWidth){
      boss.Position.x -= 1;
        if(boss.Width > 0){
          boss.Width *= -1;
          contrario = !contrario;
        }
    } 
    else if(boss.Position.x < thresholdWidth) { 
      boss.Position.x += 1;
      if(boss.Width < 0){
        boss.Width *= -1;
        contrario = !contrario;
      } 
    }

    
    if(boss.Position.y > thresholdHeight){
      boss.Position.y -= 1.0;
    } else if(boss.Position.y < thresholdHeight) {
        boss.Position.y += 1.0;
      }
    
    if(boss.Position.x == thresholdWidth && boss.Position.y == thresholdHeight){
      //boss.CurrentFrame = 6; 
      ataqueBoss = true;
      
    }

    
  BeginDrawing();

  
  ClearBackground(RAYWHITE);
  DrawTexture(background, 0, 0, RAYWHITE);
    
  for(int i = 0; i < nCoxinhas; i++){
    DrawTexture(coxinhas[i].Img, coxinhas[i].Position.x, coxinhas[i].Position.y, RAYWHITE);
    
  }  
  
    
  boss.Temp += GetFrameTime();
  if(!ataqueBoss){
      if(boss.Temp > boss.FrameSpeed){
        boss.Temp = 0;
        if(contrario){
          if(boss.CurrentFrame < 0){
            boss.CurrentFrame = 6;
          }
          boss.CurrentFrame -= 1;
        }
        else if(!contrario){
          boss.CurrentFrame += 1;
        }
      }
      boss.CurrentFrame = boss.CurrentFrame % 6; //mexer nessa variavel para deixar o andar do boss menos feio
    }
    else if(ataqueBoss){
      if(!contrario){
        if(boss.Temp > boss.FrameSpeed){
          boss.Temp = 0;
          boss.CurrentFrameAtaq += 1;
        }
        if(boss.CurrentFrameAtaq >= 7){
          ataqueBoss = false;
          boss.CurrentFrameAtaq = 0;
        }
      }
      else if(contrario){
        if(boss.Temp > boss.FrameSpeed){
          boss.CurrentFrameAtaq -= 1;
          boss.Temp = 0; //se tiver o contrario o ataque precisa percorrer ao contrario a imagem
        }
        if(boss.CurrentFrameAtaq < 0){
          boss.CurrentFrameAtaq = 6;
          ataqueBoss = false;
        }
      }
    }
    
    
  if(ataqueBoss){
    Player.Vida -= 0.5;
    estadoBoss = 2;
    ColorPlayer = GREEN;
    boss.FrameRec = (Rectangle) {boss.Width *  boss.CurrentFrameAtaq, boss.Height * estadoBoss, boss.Width, boss.Height};
  }
  else{
    estadoBoss = 1;
    ColorPlayer = RAYWHITE;
    boss.FrameRec = (Rectangle) {boss.Width *  boss.CurrentFrame, boss.Height * estadoBoss, boss.Width, boss.Height};
  }
  
  
  DrawTextureRec(boss.Img, boss.FrameRec, boss.Position, Colorboss);    
  
  if(boss.Vida <= 0){
    estadoBoss = 3;
    boss.Temp = 0;
    boss.CurrentFrame = 0;
    //boss.FrameSpeed = 8;
    while(boss.CurrentFrame !=5){
      boss.Temp += GetFrameTime();
      if(boss.Temp > boss.FrameSpeed){
        boss.Temp = 0;
        boss.CurrentFrame += 1;
 
      }
      
      boss.FrameRec = (Rectangle) {boss.Width *  boss.CurrentFrame, boss.Height * estadoBoss, boss.Width, boss.Height};
      DrawTextureRec(boss.Img, boss.FrameRec, boss.Position, Colorboss); 
      WaitTime(10);
      }
    boss.Position = (Vector2) {12000.0, 12000.0};
    boss.Collision = (Rectangle) {12000.0, 12000.0, 1.0, 1.0};
    //UnloadTexture(boss.Img);
    }
    
