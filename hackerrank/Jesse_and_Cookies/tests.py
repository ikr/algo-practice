import unittest

from solution import sweetness_increases_count, combined_cookie_sweetness


class TestSweetnessIncreasesCount(unittest.TestCase):
    def test_is_zero_in_possible_degenerate_case(self):
        self.assertEqual(sweetness_increases_count(0, tuple()), 0)

    def test_is_zero_in_impossible_degenerate_case(self):
        self.assertEqual(sweetness_increases_count(100, tuple()), -1)

    def test_possible_trivial_case(self):
        self.assertEqual(sweetness_increases_count(2, (3,)), 0)

    def test_impossible_trivial_case(self):
        self.assertEqual(sweetness_increases_count(2, (1,)), -1)

    def test_works_for_the_problem_statement_example(self):
        self.assertEqual(sweetness_increases_count(7, (1, 2, 3, 9, 10, 12)), 2)


class TestCombinedCookieSweetness(unittest.TestCase):
    def test_problem_statement_example(self):
        self.assertEqual(combined_cookie_sweetness(1, 2), 5)


if __name__ == '__main__':
    unittest.main()
