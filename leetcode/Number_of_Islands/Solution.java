import java.util.AbstractMap;

class Solution {
    public int numIslands(char[][] grid) {
        Set<Map.Entry<Integer, Integer>> toDiscover = positionsToDiscover(grid);
        int result = 0;
        while (toDiscover.size() > 0) {
            discover(grid, toDiscover, peek(toDiscover));
            result++;
        }
        return result;
    }

    private static void discover(char[][] grid, Set<Map.Entry<Integer, Integer>> toDiscover, Map.Entry<Integer, Integer> p) {
        toDiscover.remove(p);
        for (Map.Entry<Integer, Integer> ap : adjacent(grid, p)) {
            if (toDiscover.contains(ap)) {
                discover(grid, toDiscover, ap);
            }
        }
    }

    private static Set<Map.Entry<Integer, Integer>> positionsToDiscover(char[][] grid) {
        Set<Map.Entry<Integer, Integer>> result = new HashSet<>();
        for (int r = 0; r < grid.length; r++) {
            for (int c = 0; c < grid[r].length; c++) {
                if (grid[r][c] == '1') {
                    result.add(pos(r, c));
                }
            }
        }
        return result;
    }

    private static List<Map.Entry<Integer, Integer>> adjacent(char[][] grid, Map.Entry<Integer, Integer> p) {
        List<Map.Entry<Integer, Integer>> result = new ArrayList<>();
        Object[] deltas = new Object[] {pos(-1, 0), pos(0, 1), pos(1, 0), pos(0, -1)};
        for (Object d : deltas) {
            Map.Entry<Integer, Integer> dPos = (Map.Entry<Integer, Integer>)d;
            int r = row(p) + row(dPos);
            int c = col(p) + col(dPos);
            if (r >= 0 && r < grid.length && c >= 0 && c < grid[r].length && grid[r][c] == '1') {
                result.add(pos(r, c));
            }
        }
        return result;
    }

    private static Map.Entry<Integer, Integer> pos(int r, int c) {
        return new AbstractMap.SimpleEntry<>(r, c);
    }

    private static int row(Map.Entry<Integer, Integer> p) {
        return p.getKey().intValue();
    }

    private static int col(Map.Entry<Integer, Integer> p) {
        return p.getValue().intValue();
    }

    private static Map.Entry<Integer, Integer> peek(Set<Map.Entry<Integer, Integer>> s) {
        for (Map.Entry<Integer, Integer> p : s) {
            return p;
        }
        return null;
    }
}
