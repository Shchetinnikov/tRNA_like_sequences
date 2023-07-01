import Main from '@/pages/Main.vue';
import Info from '@/pages/Info.vue';
import Help from '@/pages/Help.vue';
import Seq from '@/pages/Seq.vue';
import { createRouter, createWebHistory } from 'vue-router';


const routes = [
    {
        path: '/',
        component: Main
    },
    {
        path: '/info',
        component: Info
    },
    {
        path: '/help',
        component: Help
    },
    {
        path: '/seq',
        component: Seq
    }
]

const router = createRouter({
    routes,
    history: createWebHistory(process.env.BASE_URL)
})

export default router;