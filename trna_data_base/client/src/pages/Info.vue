<template>
    <h3>TRNA sequences and description</h3>
    <hr>
    <div class="fs-5">
        <div class="row m-3">
            <div class="col-3">
                <label for="">Choose tRNA</label>
                <my-select 
                    v-model="selected.trna" 
                    :options="trnaOptions" 
                >
                </my-select>
            </div>
            <div class="col-3">
                <label for="">Choose chromosome</label>
                <my-select 
                    v-model="selected.chr" 
                    :options="chrOptions" 
                >
                </my-select>
            </div>
            <div class="col-3">
                <label for="">Choose direction</label>
                <my-select 
                    v-model="selected.direct" 
                    :options="directOptions" 
                >
                </my-select>
            </div>
        </div>
        <div class="row m-3">
            <div class="col-3">
                <label for="">Choose sorting field</label>
                <my-select 
                    v-model="selectedSort" 
                    :options="sortOptions" 
                >
                </my-select>
            </div>
        </div>
    </div>
    <div class="row">
        <div v-if="loading">
            <my-loader></my-loader>
        </div>
        <div v-else>
            <PostList 
                :posts="this.sortedPosts"
            />
        </div>
    </div>
    <div ref="observer"></div>

</template>

<script>
import PostList from "@/components/PostList.vue"
import axios from 'axios'

export default {
    components: { PostList },
    data() {
        return {
            loading: false,
            posts: [],
            selected: {
                chr: '',
                trna: '',
                direct: '',
            },
            selectedSort: 'None',
            chrOptions: [
                { value: "", name: "All" }, { value: "1", name: "chromosome-1" },
                { value: "2", name: "chromosome-2" }, { value: "3", name: "chromosome-3" },
                { value: "4", name: "chromosome-4" }, { value: "5", name: "chromosome-5" },
                { value: "6", name: "chromosome-6" }, { value: "7", name: "chromosome-7" },
                { value: "8", name: "chromosome-8" }, { value: "9", name: "chromosome-9" },
                { value: "10", name: "chromosome-10" }, { value: "11", name: "chromosome-11" },
                { value: "12", name: "chromosome-12" }, { value: "13", name: "chromosome-13" },
                { value: "14", name: "chromosome-14" }, { value: "15", name: "chromosome-15" },
                { value: "16", name: "chromosome-16" }, { value: "17", name: "chromosome-17" },
                { value: "18", name: "chromosome-18" }, { value: "19", name: "chromosome-19" },
                { value: "20", name: "chromosome-20" }, { value: "21", name: "chromosome-21" },
                { value: "22", name: "chromosome-22" }, { value: "X", name: "chromosome-X" },
                { value: "Y", name: "chromosome-Y" }, { value: "MT", name: "chromosome-MT"} ],
            trnaOptions: [
                { value: "", name: "All" },
                { value: "trna-Ala", name: "tRNA-Ala" }, { value: "trna-Arg", name: "tRNA-Arg" },
                { value: "trna-Asn", name: "tRNA-Asn" }, { value: "trna-Asp", name: "tRNA-Asp" },
                { value: "trna-Cys", name: "tRNA-Cys" }, { value: "trna-Gln", name: "tRNA-Gln" },
                { value: "trna-Glu", name: "tRNA-Glu" }, { value: "trna-Gly", name: "tRNA-Gly" },
                { value: "trna-His", name: "tRNA-His" }, { value: "trna-Ile", name: "tRNA-Ile" },
                { value: "trna-Leu", name: "tRNA-Leu" }, { value: "trna-Lys", name: "tRNA-Lys" },
                { value: "trna-Met", name: "tRNA-Met" }, { value: "trna-Phe", name: "tRNA-Phe" },
                { value: "trna-Pro", name: "tRNA-Pro" }, { value: "trna-SeC", name: "tRNA-SeC" },
                { value: "trna-Ser", name: "tRNA-Ser" }, { value: "trna-Sup", name: "tRNA-Sup" },
                { value: "trna-Thr", name: "tRNA-Thr" }, { value: "trna-Trp", name: "tRNA-Trp" },
                { value: "trna-Tyr", name: "tRNA-Tyr" }, { value: "trna-Val", name: "tRNA-Val" }],
            directOptions: [
                { value: "", name: "All" }, { value: "-", name: "3'-5'" }, { value: "+", name: "5'-3'" }],
            sortOptions: [
                { value: '', name: 'None' },
                { value: 'chromosome', name: 'Chromosome' },
                { value: 'trna', name: 'TRNA' },
                { value: 'direction', name: 'Direction' },
                { value: 'start_idx', name: 'Start position' },
                { value: 'end_idx', name: 'End position' },
                { value: 'e_value', name: 'E-value' },
            ],
            page: 1,
            limit: 20,
            totalPages: 0,                            
        }
    },
    methods: {
        async fetchPosts() {
            try {
                this.page = 1;
                this.totalPages = 0;
                const response = await axios.get('http://localhost:5000/api/info/', {
                    params: {
                        _filter: this.selected,
                        _page: this.page,
                        _limit: this.limit
                    }
                });
                // const response = await axios.get('https://jsonplaceholder.typicode.com/posts?_limit=10');
                this.posts = response.data.posts;
                this.totalPages = Math.ceil(response.data.totalCount / this.limit);
            } catch (e) {
                alert('Ошибка')
            }
        },
        async loadMorePosts() {
            if (this.page + 1 <= this.totalPages) {
                try {
                    this.page += 1;
                    const response = await axios.get('http://localhost:5000/api/info/', {
                        params: {
                            _filter: this.selected,
                            _page: this.page,
                            _limit: this.limit
                        }
                    });
                    this.posts = [...this.posts, ...response.data.posts];

                } catch (e) {
                    alert('Ошибка')
                }
            }
        },
    },
    async mounted() {
        this.loading = true;
        await this.fetchPosts();
        this.loading = false;

        const options = {
            rootMargin: "0px",
            threshold: 1.0,
        };

        const callback = (entries, oserver) => {
            if (entries[0].isIntersecting) {
                this.loadMorePosts()
            }
        };

        const observer = new IntersectionObserver(callback, options);
        observer.observe(this.$refs.observer);
    },
    computed: {
        sortedPosts() {
            if (['start_idx', 'end_idx', 'e_value'].includes(this.selectedSort)) {
                return [...this.posts].sort((post1, post2) =>
                    post1[this.selectedSort] - (post2[this.selectedSort]))
            } else {
                return [...this.posts].sort((post1, post2) =>
                    post1[this.selectedSort]?.localeCompare(post2[this.selectedSort]))
            }
        }
    },
    watch: {
        selected: {
            handler() {
                this.fetchPosts();
            },
            deep: true,
        }
    }
        
}
</script>

<style scoped>
</style>