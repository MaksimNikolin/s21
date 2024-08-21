#include <check.h>

#include "../brick_game/tetris/tetris_logic.h"

extern GameInfo_t game;

// Test for loadHighScore
START_TEST(test_loadHighScore) {
  game.high_score = 0;
  FILE *file = fopen(HIGHSCORE_FILE, "w");
  fprintf(file, "1234");
  fclose(file);

  loadHighScore();
  ck_assert_int_eq(game.high_score, 1234);

  remove(HIGHSCORE_FILE);
}
END_TEST

// Test for saveHighScore
START_TEST(test_saveHighScore) {
  game.high_score = 5678;
  saveHighScore();

  FILE *file = fopen(HIGHSCORE_FILE, "r");
  int high_score = 0;
  fscanf(file, "%d", &high_score);
  fclose(file);

  ck_assert_int_eq(high_score, 5678);

  remove(HIGHSCORE_FILE);
}
END_TEST

// Test for initGame
START_TEST(test_initGame) {
  initGame();
  ck_assert_int_eq(game.score, 0);
  ck_assert_int_eq(game.high_score, 0);
  ck_assert_int_eq(game.level, 1);
  ck_assert_int_eq(game.speed, 1);
  ck_assert_int_eq(game.pause, 0);
  ck_assert(!game.game_over);

  cleanup();
}
END_TEST

// Test for cleanup
START_TEST(test_cleanup) {
  initGame();
  cleanup();
  // No direct way to test memory free, but ensure no crash
}
END_TEST

// Test for userInput
START_TEST(test_userInput) {
  initGame();
  userInput(Pause, false);
  ck_assert_int_eq(game.pause, 1);

  userInput(Pause, false);
  ck_assert_int_eq(game.pause, 0);

  userInput(Action, false);
  ck_assert_int_eq(current_piece.rotation, 0);

  userInput(Down, false);
  dropPiece();

  userInput(Left, false);
  ck_assert_int_eq(current_piece.x, 2);

  userInput(Right, false);
  ck_assert_int_eq(current_piece.x, 3);

  cleanup();
}
END_TEST

// Test for updateCurrentState
START_TEST(test_updateCurrentState) {
  initGame();
  game.pause = 1;
  GameInfo_t info = updateCurrentState();
  ck_assert_int_eq(info.pause, 1);

  cleanup();
}
END_TEST

// Test for newPiece
START_TEST(test_newPiece) {
  initGame();
  newPiece();
  ck_assert_int_ge(current_piece.x, 0);
  ck_assert_int_ge(current_piece.y, -1);
  ck_assert_int_le(current_piece.x, WIDTH - 4);

  cleanup();
}
END_TEST

// Test for checkCollision
START_TEST(test_checkCollision) {
  initGame();
  current_piece.type = 0;
  ck_assert_int_eq(checkCollision(0, 0, 0), 0);
  game.field[0][0] = 1;
  ck_assert_int_eq(!checkCollision(0, 0, 0), 1);

  cleanup();
}
END_TEST

// Test for placePiece
START_TEST(test_placePiece) {
  initGame();
  current_piece.x = 0;
  current_piece.y = 0;
  current_piece.rotation = 0;
  current_piece.type = 0;
  placePiece();

  ck_assert_int_eq(game.field[1][0], 1);
  ck_assert_int_eq(game.field[1][1], 1);
  ck_assert_int_eq(game.field[1][2], 1);
  ck_assert_int_eq(game.field[1][3], 1);

  cleanup();
}
END_TEST

// Test for clearLines
START_TEST(test_clearLines) {
  initGame();
  for (int i = 0; i < WIDTH; ++i) {
    game.field[0][i] = 1;
  }
  clearLines();
  ck_assert_int_eq(game.score, 100);
  for (int i = 0; i < WIDTH; ++i) {
    ck_assert_int_eq(game.field[0][i], 0);
  }

  cleanup();
}
END_TEST

// Test for rotatePiece
START_TEST(test_rotatePiece) {
  initGame();
  current_piece.x = 0;
  current_piece.y = 0;
  current_piece.rotation = 0;
  rotatePiece();
  ck_assert_int_eq(current_piece.rotation, 1);

  cleanup();
}
END_TEST

// Test for movePiece
START_TEST(test_movePiece) {
  initGame();
  current_piece.x = 0;
  current_piece.y = 0;
  movePiece(1, 0);
  ck_assert_int_eq(current_piece.x, 1);
  movePiece(0, 1);
  ck_assert_int_eq(current_piece.y, 1);

  cleanup();
}
END_TEST

// Test for dropPiece
START_TEST(test_dropPiece) {
  initGame();
  current_piece.x = 0;
  current_piece.y = 0;
  current_piece.rotation = 0;
  current_piece.type = 0;
  dropPiece();
  ck_assert_int_eq(current_piece.y, -1);
}
END_TEST

// Test for spawnNewPiece
START_TEST(test_spawnNewPiece) {
  initGame();
  spawnNewPiece();
  ck_assert_int_ge(next_piece.type, 0);
  ck_assert_int_le(next_piece.type, NUM_PIECES - 1);

  cleanup();
}
END_TEST

// Suite setup
Suite *tetris_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Tetris");

  // Core test case
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_loadHighScore);
  tcase_add_test(tc_core, test_saveHighScore);
  tcase_add_test(tc_core, test_initGame);
  tcase_add_test(tc_core, test_cleanup);
  tcase_add_test(tc_core, test_userInput);
  tcase_add_test(tc_core, test_updateCurrentState);
  tcase_add_test(tc_core, test_newPiece);
  tcase_add_test(tc_core, test_checkCollision);
  tcase_add_test(tc_core, test_placePiece);
  tcase_add_test(tc_core, test_clearLines);
  tcase_add_test(tc_core, test_rotatePiece);
  tcase_add_test(tc_core, test_movePiece);
  tcase_add_test(tc_core, test_dropPiece);
  tcase_add_test(tc_core, test_spawnNewPiece);
  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int failed;
  Suite *s;
  SRunner *sr;

  s = tetris_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
