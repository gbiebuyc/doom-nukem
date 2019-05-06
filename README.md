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
Key | Action
--- | ---
Right click | Drag view
Wheel | Zoom
R | Run the game (auto saved before)
S | Save file
L | Toggle grid locking
Space | Create sector (CLOCKWISE ONLY!)
Backspace | Delete the last wall plotted when drawing a sector
Del | Delete sector under cursor
Page Up/Down | Change floor height of sector under cursor
