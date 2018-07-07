import java.util.*;

class Solution {
    public static void main(String[] args) {
        Solution s = new Solution();
        int[] nums = new int[] {-1, 0, 1, 2, -1, -4};
        for (List<Integer> triplet : s.threeSum(nums)) {
            System.out.println(triplet);
        }
    }

    public List<List<Integer>> threeSum(int[] nums) {
        Map<Integer, List<Pair>> ips = indexPairsBySum(nums);
        List<List<Integer>> result = new ArrayList<>();

        for (int i = 0; i < nums.length; i++) {
            int key = -nums[i];
            if (ips.containsKey(key)) {
                for (Pair pair : ips.get(key)) {
                    if (pair.isDistinct(i)) {
                        result.add(triplet(nums[pair.a], nums[pair.b], nums[i]));
                    }
                }
            }
        }

        return result;
    }

    private static Map<Integer, List<Pair>> indexPairsBySum(int[] nums) {
        Map<Integer, List<Pair>> result = new HashMap<>();

        for (int i = 0; i < nums.length - 1; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                final int key = nums[i] + nums[j];
                ensureContainer(result, key);
                result.get(key).add(new Pair(i, j));
            }
        }

        return result;
    }

    private static void ensureContainer(Map<Integer, List<Pair>> m, int key) {
        if (!m.containsKey(key)) {
            m.put(key, new ArrayList<>());
        }
    }

    private static class Pair {
        final int a;
        final int b;

        Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }

        boolean isDistinct(int c) {
            return c != a && c != b;
        }
    }

    private static List<Integer> triplet(int a, int b, int c) {
        return Arrays.asList(a, b, c);
    }
}
