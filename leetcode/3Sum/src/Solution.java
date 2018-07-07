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
        HashSet<TriSet> trisets = new HashSet<>();

        for (int i = 0; i < nums.length; i++) {
            int key = -nums[i];
            if (ips.containsKey(key)) {
                for (Pair pair : ips.get(key)) {
                    final List<Integer> t = triplet(nums[pair.a], nums[pair.b], nums[i]);
                    final TriSet ts = new TriSet(t);

                    if (pair.isDistinct(i) && !trisets.contains(ts)) {
                        result.add(t);
                        trisets.add(ts);
                    }
                }
            }
        }

        Collections.sort(
            result,

            Comparator.comparingInt((List<Integer> t) -> t.get(0))
                .thenComparingInt(t -> t.get(1))
                .thenComparingInt(t -> t.get(2))
        );

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

    private static class TriSet {
        final int a;
        final int b;
        final int c;

        public TriSet(List<Integer> abc) {
            a = abc.get(0);
            b = abc.get(1);
            c = abc.get(2);
        }

        @Override public int hashCode() {
            return (a - 65_000) * (b - 65_000) * (c - 65_000);
        }

        @Override public boolean equals(Object obj) {
            TriSet ots = (TriSet) obj;
            int oa = ots.a;
            int ob = ots.b;
            int oc = ots.c;
            int[] own = new int[] {a, b, c};

            return Arrays.equals(own, new int[] {oa, ob, oc})
                || Arrays.equals(own, new int[] {oa, oc, ob})
                || Arrays.equals(own, new int[] {ob, oa, oc})
                || Arrays.equals(own, new int[] {ob, oc, oa})
                || Arrays.equals(own, new int[] {oc, ob, oa})
                || Arrays.equals(own, new int[] {oc, oa, ob});
        }

        @Override public String toString() {
            return String.format("{%d, %d, %d}", a, b, c);
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

        @Override public String toString() {
            return String.format("{%d, %d}", a, b);
        }
    }

    private static List<Integer> triplet(int a, int b, int c) {
        List<Integer> result = Arrays.asList(a, b, c);
        Collections.sort(result);
        return result;
    }
}
