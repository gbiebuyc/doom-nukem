### Overview of the game's structure
```c
loop()
{
  // Poll events
  update()
  {
    // Update position and game state
  }
  render()
  {
    render_sector(t_sector *sect, t_frustum *fr)
    {
      // project vertices for each wall
      draw_floor(projdata, frustum);
      draw_wall(projdata, frustum)
      {
        // recursive call
        render_sector(neighbor_sect, new_frustum);
      }
    }
  }
}
```
### Editor keys:
- R = Run the game
- S = Save file
- L = Toggle grid locking
- Right click = drag view
- Wheel = zoom
