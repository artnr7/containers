# add-auto-load-safe-path ../src/

break brick_game/tetris/tetris_src/tetris_moving.c:107
commands
  display rotation_matrix_height
  display rotation_matrix_width
  display i
  display j
  display try_to_move_x
end


break brick_game/tetris/tetris_src/tetris_collision.c:24
commands
  display rotation_matrix_height
  display rotation_matrix_width
  display k
  display l
  display rot_matr_i
  display rot_matr_j
  display *try_to_move_x
end


# # break brick_game/tetris/tetris_src/tetris_moving.c:141
# # commands
# #   display k
# #   display l
# #   display i
# #   display j
# #   display rotation_matrix_height
# #   display rotation_matrix_width
# #   display rotation_matrix_height-(l-j)-1
# #   display j+k-i
# # end

# break brick_game/tetris/tetris_src/tetris_rows_hit.c:39
# commands
#   display i
#   display j
#   display full_row_i
# end

# break brick_game/tetris/tetris_backend.c:50
# commands
#   display old_time
#   display speed_time
# end

# break brick_game/tetris/tetris_src/tetris_timer.c:16
# commands
#   display sec
#   display usec
# end