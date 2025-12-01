# Ray Tracer

Este projeto é uma implementação de um **Ray Tracer** em C++, inspirado no projeto  
**"Ray Tracing in One Weekend"** (Peter Shirley), porém expandida com:

- Sistema modular com arquivos `.h` e `.cpp`
- Janela com SDL2 
- Movimento de câmera
- Arquitetura orientada a objetos
  
---

## Funcionalidades

- Renderização usando *path tracing* básico  
- Movimento de câmera em tempo real  
- Suporte ao objeto `sphere`  
- Materiais suportados:
  - Lambertian (difuso)
  - Metal
- Vetor 3D otimizado (`vec3`)
- Sistema genérico de colisão (`hittable`)
- Sistema de objetos (`hittable_list`)
- Renderização em buffer e exibição com SDL2

---

## Dependências

- **SDL2**
- C++17 ou superior
- g++ / clang++

### Instalar SDL2 (Linux – Ubuntu/Debian)

```bash
sudo apt-get install libsdl2-dev
