import static java.util.stream.Collectors.*;

class Solution {
    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        recur(new ArrayList<Integer>(), arrList(nums), result);
        return result;
    }

    private static void recur(ArrayList<Integer> prefix, ArrayList<Integer> pool, List<List<Integer>> result) {
        if (pool.size() == 0) {
            result.add(prefix);
            return;
        }

        for (int i = 0; i < pool.size(); ++i) {
            int x = pool.get(i);
            ArrayList<Integer> prefix1 = arrList(prefix);
            ArrayList<Integer> pool1 = arrList(pool);
            prefix1.add(x);
            pool1.remove(i);
            recur(prefix1, pool1, result);
        }
    }

    private static ArrayList<Integer> arrList(int[] xs) {
        return Arrays.stream(xs).boxed().collect(toCollection(ArrayList::new));
    }

    private static ArrayList<Integer> arrList(ArrayList<Integer> xs) {
        ArrayList<Integer> result = new ArrayList<>();
        result.addAll(xs);
        return result;
    }
}
