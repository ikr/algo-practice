#!/usr/bin/env python3


import unittest


from solution import *


class TestWordPlacingsFromLine(unittest.TestCase):
    def test_is_an_empty_tuple_on_all_pluses(self):
        line = '++++++++++'
        self.assertEqual(word_placings_from_line(line, (0, 0), (0, 1)), tuple())

    def test_works_on_a_second_horizontal_line(self):
        line = '++---+++++'
        self.assertEqual(
            word_placings_from_line(line, (1, 0), (0, 1)),
            (((1, 2), (1, 3), (1, 4)),)
        )

    def test_ignores_one_letter_places(self):
        self.assertEqual(word_placings_from_line('+-+', (0, 0), (0, 1)), ())

    def test_accepts_two_words_in_a_line(self):
        line = '+---+++---'
        self.assertEqual(
            word_placings_from_line(line, (0, 0), (0, 1)),
            (
                ((0, 1), (0, 2), (0, 3)),
                ((0, 7), (0, 8), (0, 9))
            )
        )


class TestTranspose(unittest.TestCase):
    def test_works(self):
        l1 = '--'
        l2 = '+-'
        self.assertEqual(transpose((l1, l2)), ('-+', '--'))


class TestWordPlacings(unittest.TestCase):
    def test_works(self):
        l1 = '+++'
        l2 = '+--'
        l3 = '--+'
        self.assertEqual(
            word_placings((l1, l2, l3), (0, 1)),
            (((1, 1), (1, 2)), ((2, 0), (2, 1)))
        )


if __name__ == '__main__':
    unittest.main()
