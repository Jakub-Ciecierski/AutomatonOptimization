import unittest
import src.main as main

class TestHomenda(unittest.TestCase):
    def test_homenda_passed(self):
        test_score = 100

        passed = main.is_homenda(test_score)

        self.assertTrue(passed)

    def test_homenda_not_passed(self):
        test_score = 99

        passed = main.is_homenda(test_score)

        self.assertFalse(passed)
