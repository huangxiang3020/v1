# v1
  
- [x] Left-Handed Coordinate 
![Coordinate](/img/coordinate.png)

- [x] $p = proj * view * model * \bar{p} $
$$\left[ \begin{matrix}
   x \\
   y \\
   z \\
   1 
  \end{matrix}
  \right] = \left[
 \begin{matrix}
   1 & 0 & 0 & t_x \\
   0 & 1 & 0 & t_y \\
   0 & 0 & 1 & t_z \\
   0 & 0 & 0 & 1
  \end{matrix}
  \right] \left[
 \begin{matrix}
   \bar{x} \\
   \bar{y} \\
   \bar{z} \\
   1
  \end{matrix}
  \right]$$

- [ ] Desgin (provisional)
```mermaid
graph TB
    subgraph Graphics
    Device
    Mesh
    Shader
    Texture
    end
    
    subgraph Node
      Position
      Rotation
      Scale
      Parent
      Children
      subgraph Component
        awake
        onEnable
        start
        update
        lateUpdate
        onDisable
        onDestroy
      end
    end

    subgraph Scene
      startPhase
      updatePhase
      lateUpdatePhase
    end
    subgraph Systems
      TimeSystem
      InputSystem
      System3
      System4
    end

    Scene-->Node
    Scene.->Systems

    Camera
    Render
    Material
    Material.->Shader
    Material.->Texture
    Render.->Material
    Render.->Mesh
    Component---Camera
    Component---Render
    Device-->Mesh
    Device-->Shader
    Device-->Texture
```