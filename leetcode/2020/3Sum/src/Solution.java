import java.util.*;

class Solution {
    public static void main(String[] args) {
        Solution s = new Solution();
        int[] nums = new int[] {0, 0, 0};
        for (List<Integer> triplet : s.threeSum(nums)) {
            System.out.println(triplet);
        }
    }

    public List<List<Integer>> threeSum(int[] nums) {
        Map<Integer, List<Integer>> ibv = indicesByValue(nums);
        if (isDegenerateCase(ibv)) return degenerateCaseSolution(ibv);

        List<List<Integer>> result = new ArrayList<>();
        HashSet<TriSet> trisets = new HashSet<>();

        for (int i = 0; i < nums.length - 1; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                int key = -(nums[i] + nums[j]);
                if (ibv.containsKey(key)) {
                    for (int r : ibv.get(key)) {
                        if (r == i || r == j) continue;

                        List<Integer> t = triplet(nums[r], nums[i], nums[j]);
                        TriSet ts = new TriSet(t);

                        if (!trisets.contains(ts)) {
                            result.add(t);
                            trisets.add(ts);
                        }
                    }
                }
            }
        }

        return result;
    }

    private static Map<Integer, List<Integer>> indicesByValue(int[] nums) {
        Map<Integer, List<Integer>> result = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            if (!result.containsKey(nums[i])) {
                result.put(nums[i], new ArrayList<>());
            }

            result.get(nums[i]).add(i);
        }
        return result;
    }

    private static boolean isDegenerateCase(Map<Integer, List<Integer>> ibv) {
        return ibv.size() == 1;
    }

    private static List<List<Integer>> degenerateCaseSolution(Map<Integer, List<Integer>> ibv) {
        int val = ibv.keySet().iterator().next();
        int indicesCount = ibv.get(val).size();
        List<List<Integer>> result = new ArrayList<>();

        if (indicesCount > 2 && val == 0) {
            result.add(triplet(0, 0, 0));
        }

        return result;
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

    private static List<Integer> triplet(int a, int b, int c) {
        return Arrays.asList(a, b, c);
    }
}
