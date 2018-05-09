import java.util.*;
import java.util.stream.IntStream;

public class Solution {
    public static final int HOP_LENGTH = 6;

    static int[] bfs(int n, int m, int[][] edges, int s) {
        return distances(hops(n, graph(edges), s));
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int q = in.nextInt();

        for (int a0 = 0; a0 < q; a0++) {
            int n = in.nextInt();
            int m = in.nextInt();
            int[][] edges = new int[m][2];

            for (int edges_i = 0; edges_i < m; edges_i++) {
                for (int edges_j = 0; edges_j < 2; edges_j++) {
                    edges[edges_i][edges_j] = in.nextInt();
                }
            }

            int s = in.nextInt();
            int[] result = bfs(n, m, edges, s);

            for (int i = 0; i < result.length; i++) {
                System.out.print(result[i] + (i != result.length - 1 ? " " : ""));
            }

            System.out.println();
        }
        in.close();
    }

    private static int[] distances(SortedMap<Integer, Integer> hs) {
        int[] result = new int[hs.size() - 1];
        int i = 0;

        for (Integer k : hs.keySet()) {
            if (hs.get(k) == 0) continue;
            result[i] = (hs.get(k) == -1) ? -1 : hs.get(k) * HOP_LENGTH;
            i++;
        }

        return result;
    }

    private static SortedMap<Integer, Integer> hops(int vCount, Map<Integer, List<Integer>> graph, int source) {
        SortedMap<Integer, Integer> result = new TreeMap<>();
        IntStream.rangeClosed(1, vCount).forEach(i -> result.put(i, i == source ? 0 : -1));

        Queue<Integer> q = new LinkedList<>();
        q.add(source);

        while (q.size() > 0) {
            int current = q.remove();
            if (!graph.containsKey(current)) continue;

            for (int adjacent : graph.get(current)) {
                if (result.get(adjacent) == -1) {
                    result.put(adjacent, result.get(current) + 1);
                    q.add(adjacent);
                }
            }
        }

        return result;
    }

    private static Map<Integer, List<Integer>> graph(int[][] edges) {
        HashMap<Integer, List<Integer>> result = new HashMap<>();

        for (int[] pair : edges) {
            if (!result.containsKey(pair[0])) {
                result.put(pair[0], new LinkedList<>());
            }

            result.get(pair[0]).add(pair[1]);
        }

        return result;
    }
}
